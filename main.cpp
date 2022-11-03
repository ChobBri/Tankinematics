/*******************************************************************************************
*
*   Team Jasper (20) Basic Framework
*
********************************************************************************************/

#include "raylib.h"
#include "raygui.h"
#include "PersistentData.hpp"
#include <string.h>
#include <stdlib.h>

namespace globals {
        enum gameStates {Title = 0, MainMenu, LevelFilter, Success, History, Simulation};
        static gameStates currentState = Title;
        static bool quitFlag = false;
        int frameCounter = 0;

        void setCurrentState(globals::gameStates newState){
            globals::currentState = newState;
            return;
        }
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
                //
            } break;

            case globals::History: {
                if (CheckCollisionPointRec(GetMousePosition(), backBB) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){ //Back button clicked
                    globals::setCurrentState(globals::MainMenu);
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

                    DrawText("history_placeholder", originVector.x, originVector.y, 25, DARKGRAY);

                    DrawTexture(backButton_T, backBP.x, backBP.y, WHITE);
                } break;

                case globals::Simulation: {
                    DrawText("simulation_placeholder", originVector.x, originVector.y, 25, DARKGRAY);

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
    UnloadTexture(mainMenuBackground_T);
    UnloadTexture(historyButton_T);
    UnloadTexture(playButton_T);
    UnloadTexture(filterButton_T);
    UnloadTexture(exitButton_T);    

    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
