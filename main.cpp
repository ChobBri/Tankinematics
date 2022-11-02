/*******************************************************************************************
*
*   Team Jasper (20) Basic Framework
*
********************************************************************************************/

#include "raylib.h"
#include "PersistentData.hpp"
#include <string.h>
#include <stdlib.h>

namespace globals {
        enum gameStates {TITLE = 0, MAIN_MENU, ANGLE_LEVEL, WIND_LEVEL, SUCCESS, FAILURE, HINT, HISTORY, SIMULATION};
        static gameStates currentState = TITLE;
        
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
    
    //globals
    int frameCounter = 0;
    bool quitFlag = false;

    //Load sprites / backgrounds
    Texture2D titleScreenLogo_T = LoadTexture("resources/titleScreenLogo.png");
    
    Texture2D backButton_T = LoadTexture("resources/backButton.png");

    Texture2D mainMenuBackground_T = LoadTexture("resources/mainMenuBackground.png");
    Texture2D historyButton_T = LoadTexture("resources/historyButton.png");
    Texture2D angleButton_T = LoadTexture("resources/angleButton.png");
    Texture2D windButton_T = LoadTexture("resources/windButton.png");
    Texture2D exitButton_T = LoadTexture("resources/exitButton.png");

    //Main menu 
    //Define button placement vectors (BPs). BPs are used to define where to draw textures which overlay onto rectangles. 
    Vector2 historyBP = {355, 400};
    Vector2 windLevelBP = {355, 270};
    Vector2 angleLevelBP = {485, 270};
    Vector2 exitBP = {10, 490};
    Vector2 backBP = {10, 490};

    //Define button bounds (BBs)
    //Rectangles which are under their respective textures. Done this way so you can use intersection-detection methods which use rectangles and points. 
    Rectangle historyBB = {historyBP.x, historyBP.y, 250, 40};
    Rectangle windLevelBB = {windLevelBP.x, windLevelBP.y, 120, 120};
    Rectangle angleLevelBB = {angleLevelBP.x, angleLevelBP.y, 120, 120};
    Rectangle exitBB = {exitBP.x, exitBP.y, 40, 40};
    Rectangle backBB = {backBP.x, backBP.y, 40, 40};

    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose() && !quitFlag)        // Detect window close button or ESC key or set quitFlag to true
    {
        switch(globals::currentState) { //Calculations / variable changes to be performed depending on state. This switch case doesn't handle drawing.
            case globals::TITLE: {
                frameCounter++;
                if (frameCounter / targetFPS >= titleScreenTime) //If we've been at title for specified number of seconds, switch to main menu
                    globals::setCurrentState(globals::MAIN_MENU);
            } break;

            case globals::MAIN_MENU: {
                if (CheckCollisionPointRec(GetMousePosition(), exitBB) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){ //Exit Button Clicked
                    quitFlag = true;
                } else if (CheckCollisionPointRec(GetMousePosition(), windLevelBB) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){ //Wind level button Clicked
                    globals::setCurrentState(globals::WIND_LEVEL);
                } else if (CheckCollisionPointRec(GetMousePosition(), angleLevelBB) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){ //Angle level button Clicked
                    globals::setCurrentState(globals::ANGLE_LEVEL);
                } else if (CheckCollisionPointRec(GetMousePosition(), historyBB) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){ //History button clicked
                    globals::setCurrentState(globals::HISTORY);
                }
            } break;

            case globals::ANGLE_LEVEL: {
                if (CheckCollisionPointRec(GetMousePosition(), backBB) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){ //Back button clicked
                    globals::setCurrentState(globals::MAIN_MENU);
                }
            } break;

            case globals::WIND_LEVEL: {
                if (CheckCollisionPointRec(GetMousePosition(), backBB) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){ //Back button clicked
                    globals::setCurrentState(globals::MAIN_MENU);
                }
            } break;

            case globals::SUCCESS: {
                //
            } break;

            case globals::FAILURE: {
                //
            } break;

            case globals::HINT: {
                //
            } break;

            case globals::HISTORY: {
                if (CheckCollisionPointRec(GetMousePosition(), backBB) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){ //Back button clicked
                    globals::setCurrentState(globals::MAIN_MENU);
                }
            } break;

            case globals::SIMULATION: {
                //
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

            if (globals::currentState != globals::TITLE && globals::currentState != globals::MAIN_MENU){
                DrawTexture(backButton_T, backBP.x, backBP.y, WHITE);
            }

            switch(globals::currentState) {
                case globals::TITLE: {
                    DrawTexture(titleScreenLogo_T, 0, 0, WHITE);

                    if (frameCounter % targetFPS >= 0 && frameCounter % targetFPS < 15){ //This just changes the loading text every 0.25 (15/60th of a) second.
                        DrawText("Loading", 385, 450, 60, BLACK);
                    } else if (frameCounter % targetFPS >= 16 && frameCounter % targetFPS < 30){
                        DrawText("Loading .", 385, 450, 60, BLACK);
                    } else if (frameCounter % targetFPS >= 30 && frameCounter % targetFPS < 45){
                        DrawText("Loading . . ", 385, 450, 60, BLACK);
                    } else if (frameCounter % targetFPS >= 45 && frameCounter % targetFPS < 60){
                        DrawText("Loading . . . ", 385, 450, 60, BLACK);
                    }
                } break;

                case globals::MAIN_MENU: {
                    DrawTexture(mainMenuBackground_T, 0, 0, WHITE);

                    DrawTexture(windButton_T, windLevelBP.x, windLevelBP.y, WHITE);
                    DrawTexture(angleButton_T, angleLevelBP.x, angleLevelBP.y, WHITE);
                    DrawTexture(historyButton_T, historyBP.x, historyBP.y, WHITE);
                    DrawTexture(exitButton_T, exitBP.x, exitBP.y, WHITE);

                } break;

                case globals::ANGLE_LEVEL: {
                    DrawText("angle_level_placeholder", originVector.x, originVector.y, 25, DARKGRAY);
                } break;

                case globals::WIND_LEVEL: {
                    DrawText("wind_level_placeholder", originVector.x, originVector.y, 25, DARKGRAY);
                } break;

                case globals::SUCCESS: {
                    DrawText("success_placeholder", originVector.x, originVector.y, 25, DARKGRAY);
                } break;

                case globals::FAILURE: {
                    DrawText("failure_placeholder", originVector.x, originVector.y, 25, DARKGRAY);
                } break;

                case globals::HINT: {
                    DrawText("hint_placeholder", originVector.x, originVector.y, 25, DARKGRAY);
                } break;

                case globals::HISTORY: {
                    DrawText("history_placeholder", originVector.x, originVector.y, 25, DARKGRAY);
                } break;

                case globals::SIMULATION: {
                    DrawText("simulation_placeholder", originVector.x, originVector.y, 25, DARKGRAY);
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
    UnloadTexture(angleButton_T);
    UnloadTexture(windButton_T);
    UnloadTexture(exitButton_T);    

    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
