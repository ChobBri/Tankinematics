/*******************************************************************************************
*
*   Team Jasper (20) Basic Framework
*
********************************************************************************************/

#include "raylib.h"
#include "Globals.hpp"
#include <string.h>
#include <stdlib.h>

#define MAX_CHARS   255

int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 1920/2; //Keep that gorgeous 16:9 ratio 
    const int screenHeight = 1080/2;
    const int targetFPS = 60; //BE CAREFUL IF CHANGING: this value is used in calculating time delays, for animations, etc.
    const int titleScreenTime = 2; 
    const Vector2 originVector = {0, 0}; 

    InitWindow(screenWidth, screenHeight, "Tankinematics!");
    SetTargetFPS(targetFPS);

    //Load and set window icon
    //NOT WORKING, ICON MUST BE "IN R8G8B8A8 FORMAT"
    // Image windowIcon = LoadImage("resources/windowIcon.ico");
    // SetWindowIcon(windowIcon);

    //Set up globals (currentState, etc)
    //Note that these are initialized to "TITLE" and "69" by default (in Globals.cpp), but you can override that here.
    // Globals::currentState = MAIN_MENU;
    // Globals::otherGlobalVariable = 69 + 1; //example of other global variable
    
    //Globals
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
        switch(Globals::currentState) { //Calculations / variable changes to be performed depending on state. This switch case doesn't handle drawing.
            case TITLE: {
                frameCounter++;
                if (frameCounter / targetFPS >= titleScreenTime) //If we've been at title for specified number of seconds, switch to main menu
                    Globals::setCurrentState(MAIN_MENU);
            } break;

            case MAIN_MENU: {
                if (CheckCollisionPointRec(GetMousePosition(), exitBB) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){ //Exit Button Clicked
                    quitFlag = true;
                } else if (CheckCollisionPointRec(GetMousePosition(), windLevelBB) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){ //Wind level button Clicked
                    Globals::setCurrentState(WIND_LEVEL);
                } else if (CheckCollisionPointRec(GetMousePosition(), angleLevelBB) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){ //Angle level button Clicked
                    Globals::setCurrentState(ANGLE_LEVEL);
                } else if (CheckCollisionPointRec(GetMousePosition(), historyBB) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){ //History button clicked
                    Globals::setCurrentState(HISTORY);
                }
            } break;

            case ANGLE_LEVEL: {
                if (CheckCollisionPointRec(GetMousePosition(), backBB) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){ //Back button clicked
                    Globals::setCurrentState(MAIN_MENU);
                }
            } break;

            case WIND_LEVEL: {
                if (CheckCollisionPointRec(GetMousePosition(), backBB) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){ //Back button clicked
                    Globals::setCurrentState(MAIN_MENU);
                }
            } break;

            case SUCCESS: {
                //
            } break;

            case FAILURE: {
                //
            } break;

            case HINT: {
                //
            } break;

            case HISTORY: {
                if (CheckCollisionPointRec(GetMousePosition(), backBB) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){ //Back button clicked
                    Globals::setCurrentState(MAIN_MENU);
                }
            } break;

            case SIMULATION: {
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

            if (Globals::currentState != TITLE && Globals::currentState != MAIN_MENU){
                DrawTexture(backButton_T, backBP.x, backBP.y, WHITE);
            }

            switch(Globals::currentState) {
                case TITLE: {
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

                case MAIN_MENU: {
                    DrawTexture(mainMenuBackground_T, 0, 0, WHITE);

                    DrawTexture(windButton_T, windLevelBP.x, windLevelBP.y, WHITE);
                    DrawTexture(angleButton_T, angleLevelBP.x, angleLevelBP.y, WHITE);
                    DrawTexture(historyButton_T, historyBP.x, historyBP.y, WHITE);
                    DrawTexture(exitButton_T, exitBP.x, exitBP.y, WHITE);

                } break;

                case ANGLE_LEVEL: {
                    DrawText("angle_level_placeholder", originVector.x, originVector.y, 25, DARKGRAY);
                } break;

                case WIND_LEVEL: {
                    DrawText("wind_level_placeholder", originVector.x, originVector.y, 25, DARKGRAY);
                } break;

                case SUCCESS: {
                    DrawText("success_placeholder", originVector.x, originVector.y, 25, DARKGRAY);
                } break;

                case FAILURE: {
                    DrawText("failure_placeholder", originVector.x, originVector.y, 25, DARKGRAY);
                } break;

                case HINT: {
                    DrawText("hint_placeholder", originVector.x, originVector.y, 25, DARKGRAY);
                } break;

                case HISTORY: {
                    DrawText("history_placeholder", originVector.x, originVector.y, 25, DARKGRAY);
                } break;

                case SIMULATION: {
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
