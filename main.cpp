/*******************************************************************************************
*
*   Team Jasper (20) Basic Framework
*
********************************************************************************************/


#include "raylib.h"
#include "PersistentData.hpp"
#include <string.h>
#include <stdlib.h>
#include <iostream>

namespace globals {
        enum gameStates {Title = 0, MainMenu, LevelFilter, Success, History, Simulation};
        static gameStates currentState = Title;
        static bool quitFlag = false;
        int frameCounter = 0;
        Level simulationArgument;

        void setCurrentState(globals::gameStates newState){
            globals::currentState = newState;
            return;
        }
}

//test

struct replayButton {
    Rectangle button;
    int index = 0;
};

const char* levelTypeToString(Level::LevelType levelType) {
    switch (levelType)
        {
        case 0:
            return "Gravity";
            break;
        case 1:
            return "Angle";
            break;
        case 2:
            return "InitSpeed";
            break;
        case 3:
            return "InitVelX";
            break;
        default:
            return "InitVelY";
            break;
        }
}
/**
 * Draws a history entry for given level in specified postion. 
 * 
 * Returns a vector defining the replay button rectangle and 
 * index of this play button within "allLevels" vector
*/
replayButton drawHistoryEntry(Level level, int position){
    //for readability
    int leftBoxEdge = 244;
    int topBoxEdge = (32 + (position - 1) * 48);
    int boxWidth = 472;
    int boxHeight = 44;
    int fontSize = 4;

    //Draw rectangle
    DrawRectangle(leftBoxEdge, topBoxEdge, boxWidth, boxHeight, LIGHTGRAY);

    //Draw level stats
    DrawText(TextFormat("Total Attempts: %d", level.totalAttempts),             leftBoxEdge+4, topBoxEdge+4 + 0,    fontSize, BLACK);
    DrawText(TextFormat("Successful Attempts: %d", level.successfulAttempts),   leftBoxEdge+4, topBoxEdge+4 + 10,   fontSize, BLACK);
    DrawText(levelTypeToString(level.levelType),                                leftBoxEdge+4, topBoxEdge+4 + 20,   fontSize, BLACK);

    //Draw play button and text
    Rectangle playButton = {leftBoxEdge + boxWidth - 94, topBoxEdge + 4, 90, boxHeight-8};
    DrawRectangleRec(playButton, LIME);
    DrawText(TextFormat("Replay"), leftBoxEdge + boxWidth - 90, topBoxEdge + 8, 26, WHITE);

    replayButton returnValue{replayButton{playButton, position - 1}};

    return returnValue;
}

int main(void)
{
    PersistentData::debugLevel();

    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 1920/2; //Keep that gorgeous 16:9 ratio 
    const int screenHeight = 1080/2;
    const int targetFPS = 60; //BE CAREFUL IF CHANGING: this value is used in calculating time delays, for animations, etc.
    const int titleScreenTime = 2; 
    const Vector2 originVector = {0, 0}; 

    InitWindow(screenWidth, screenHeight, "Tankinematics!");
    SetTargetFPS(targetFPS);

    //Load sprites / backgrounds
    Texture2D titleScreenLogo_T = LoadTexture("resources/titleScreenLogo.png");
    Texture2D genericDarkenedBackground_T = LoadTexture("resources/genericDarkenedBackground.png");
    
    Texture2D backButton_T = LoadTexture("resources/backButton.png");

    Texture2D mainMenuBackground_T = LoadTexture("resources/mainMenuBackground.png");
    Texture2D historyButton_T = LoadTexture("resources/historyButton.png");
    Texture2D playButton_T = LoadTexture("resources/playButton.png");
    Texture2D filterButton_T = LoadTexture("resources/filterButton.png");
    Texture2D exitButton_T = LoadTexture("resources/exitButton.png");

    //Define button placement vectors (BPs). BPs are used to define where to draw textures which overlay onto rectangles. 
    Vector2 historyBP = {355, 400};
    Vector2 playBP = {355, 270};
    Vector2 filterBP = {485, 270};
    Vector2 exitBP = {10, 490};
    Vector2 backBP = {10, 490};

    //Define button bounds (BBs)
    //Rectangles which are under their respective textures. Done this way so you can use intersection-detection methods which use rectangles and points. 
    Rectangle historyBB = {historyBP.x, historyBP.y, 250, 40};
    Rectangle playBB = {playBP.x, playBP.y, 120, 120};
    Rectangle filterBB = {filterBP.x, filterBP.y, 120, 120};
    Rectangle exitBB = {exitBP.x, exitBP.y, 40, 40};
    Rectangle backBB = {backBP.x, backBP.y, 40, 40};

    //--------------------------------------------------------------------------------------
    //test
    
    //This will eventually be "allLevels"
    vector<Level> levelList;

    //Generate 10 levels with varying information
    for (int i = 0; i < 8; i++){
        levelList.emplace_back(Level{
            1.2f*i, //gravity
            15.0f*i, //angle
            9.2f*i, //speed
            {1.0f*i, 2.0f*i}, //init velocity
            {3.0f*i, 1.23f*i}, //tank position
            {1.1f*i, 6.1f*i}, //target position
            {{("SAMPLEHINT" + to_string(i))}}, //hints
            ("SAMPLESOLUTION" + to_string(i)), //solution
            true, //angle override flag
            2*i, //total attempts
            i, //successful attempts
            42.0f*i, //time
            (i%2) ? Level::LevelType::Gravity : Level::LevelType::Angle //level type 
        });
    }

    Rectangle historyBox = {240, 30, 480, 480}; //This is the grey box that contains all history entries

    vector<replayButton> replayButtonList;

    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose() && !globals::quitFlag)        // Detect window close button or ESC key or set quitFlag to true
    {
        switch(globals::currentState) { //Calculations / variable changes to be performed depending on state. This switch case doesn't handle drawing.
            case globals::Title: {
                globals::frameCounter++;
                if (globals::frameCounter / targetFPS >= titleScreenTime) //If we've been at title for specified number of seconds, switch to main menu
                    globals::setCurrentState(globals::MainMenu);
            } break;

            case globals::MainMenu: {
                if (CheckCollisionPointRec(GetMousePosition(), exitBB) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){ //Exit Button Clicked
                    globals::quitFlag = true;
                } else if (CheckCollisionPointRec(GetMousePosition(), playBB) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){ //Play button clicked
                    globals::simulationArgument = levelList[5];
                    globals::setCurrentState(globals::Simulation);
                } else if (CheckCollisionPointRec(GetMousePosition(), filterBB) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){ //Filter button Clicked
                    globals::setCurrentState(globals::LevelFilter);
                } else if (CheckCollisionPointRec(GetMousePosition(), historyBB) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){ //History button clicked
                    globals::setCurrentState(globals::History);
                }
            } break;

            case globals::LevelFilter: {
                if (CheckCollisionPointRec(GetMousePosition(), backBB) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){ //Back button clicked
                    globals::setCurrentState(globals::MainMenu);
                }
            } break;

            case globals::Success: {
                //content
            } break;

            case globals::History: {
                if (CheckCollisionPointRec(GetMousePosition(), backBB) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){ //Back button clicked
                    globals::setCurrentState(globals::MainMenu);
                }

                for (replayButton i : replayButtonList){
                    if (CheckCollisionPointRec(GetMousePosition(), i.button) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){ //replay button clicked
                        globals::simulationArgument = levelList[i.index];
                        globals::setCurrentState(globals::Simulation);   
                    }
                }

            } break;

            case globals::Simulation: {
                if (CheckCollisionPointRec(GetMousePosition(), backBB) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){ //Back button clicked
                    globals::setCurrentState(globals::MainMenu);
                }
            } break;

            default: {
                //shouldn't get here, means we're in an undefined state
            } break;
        }

        
        //----------------------------------------------------------------------------------
        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

            switch(globals::currentState) {
                case globals::Title: {
                    DrawTexture(titleScreenLogo_T, 0, 0, WHITE);

                    if (globals::frameCounter % targetFPS >= 0 && globals::frameCounter % targetFPS < 15){ //This just changes the loading text every 0.25 (15/60th of a) second.
                        DrawText("Loading", 385, 450, 60, BLACK);
                    } else if (globals::frameCounter % targetFPS >= 16 && globals::frameCounter % targetFPS < 30){
                        DrawText("Loading .", 385, 450, 60, BLACK);
                    } else if (globals::frameCounter % targetFPS >= 30 && globals::frameCounter % targetFPS < 45){
                        DrawText("Loading . . ", 385, 450, 60, BLACK);
                    } else if (globals::frameCounter % targetFPS >= 45 && globals::frameCounter % targetFPS < 60){
                        DrawText("Loading . . . ", 385, 450, 60, BLACK);
                    }
                } break;

                case globals::MainMenu: {
                    DrawTexture(mainMenuBackground_T, 0, 0, WHITE);

                    DrawTexture(playButton_T, playBP.x, playBP.y, WHITE);
                    DrawTexture(filterButton_T, filterBP.x, filterBP.y, WHITE);
                    DrawTexture(historyButton_T, historyBP.x, historyBP.y, WHITE);
                    DrawTexture(exitButton_T, exitBP.x, exitBP.y, WHITE);

                } break;

                case globals::LevelFilter: {
                    DrawTexture(genericDarkenedBackground_T, originVector.x, originVector.y, WHITE);

                    DrawText("level_filter_placeholder", originVector.x, originVector.y, 25, DARKGRAY);

                    DrawTexture(backButton_T, backBP.x, backBP.y, WHITE);
                } break;

                case globals::Success: {
                    DrawTexture(genericDarkenedBackground_T, originVector.x, originVector.y, WHITE);

                    DrawText("success_placeholder", originVector.x, originVector.y, 25, DARKGRAY);

                    DrawTexture(backButton_T, backBP.x, backBP.y, WHITE);
                } break;

                case globals::History: {
                    DrawTexture(genericDarkenedBackground_T, originVector.x, originVector.y, WHITE);

                    DrawRectangleRec(historyBox, DARKGRAY);

                    int position = 1;
                    replayButtonList.clear();
                    replayButton temp;

                    for (Level i : levelList){ //This both draws all the history entries AND stores the position of their replay buttons 
                        temp = drawHistoryEntry(i, position);
                        replayButtonList.push_back(temp);
                        position++;
                    }

                    DrawTexture(backButton_T, backBP.x, backBP.y, WHITE);
                } break;

                case globals::Simulation: {
                    DrawText("simulation_placeholder", originVector.x, originVector.y, 25, DARKGRAY);
                    DrawText(TextFormat("\n\nLevel info:\nGravity: %f\nAngle: %f\n", globals::simulationArgument.gravity, globals::simulationArgument.angle), originVector.x, originVector.y, 25, DARKGRAY);

                    DrawTexture(backButton_T, backBP.x, backBP.y, WHITE);
                } break;

                default: {
                    //error, shouldn't get here
                } break;
        }

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadTexture(backButton_T); //Free up mem again
    UnloadTexture(titleScreenLogo_T);
    UnloadTexture(genericDarkenedBackground_T);
    UnloadTexture(mainMenuBackground_T);
    UnloadTexture(historyButton_T);
    UnloadTexture(playButton_T);
    UnloadTexture(filterButton_T);
    UnloadTexture(exitButton_T);
    

    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
