/*******************************************************************************************
*
*   raylib [core] example - 2d camera
*
*   This example has been created using raylib 1.5 (www.raylib.com)
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*
*   Copyright (c) 2016 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include "raylib.h"
#include <string.h>
#include <stdlib.h>

#define MAX_CHARS   255

int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 1920/2;
    const int screenHeight = 1080/2;
    const int targetFPS = 60;
    const int titleScreenTime = 2;

    InitWindow(screenWidth, screenHeight, "Tankinematics!");
    SetTargetFPS(targetFPS);

    //Load and set window icon
    //NOT WORKING, ICON MUST BE "IN R8G8B8A8 FORMAT"
    // Image windowIcon = LoadImage("resources/windowIcon.ico");
    // SetWindowIcon(windowIcon);

    //Setting up enumerated state type, setting starting state to TITLE
    enum gameStates {TITLE = 0, MAIN_MENU, ANGLE_LEVEL, WIND_LEVEL, SUCCESS, FAILURE, HINT, HISTORY, SIMULATION};
    gameStates currState = TITLE;
    
    //Globals
    int frameCounter = 0;
    Vector2 originVector = {0, 0};
    bool quitFlag = false;

    //Load sprites
    Texture2D titleScreenLogo_T = LoadTexture("resources/titleScreenLogo.png");
    
    Texture2D backButton_T = LoadTexture("resources/backButton.png");

    Texture2D mainMenuBackground_T = LoadTexture("resources/mainMenuBackground.png");
    Texture2D historyButton_T = LoadTexture("resources/historyButton.png");
    Texture2D angleButton_T = LoadTexture("resources/angleButton.png");
    Texture2D windButton_T = LoadTexture("resources/windButton.png");
    Texture2D exitButton_T = LoadTexture("resources/exitButton.png");

    //Main menu 
    //Define button placement vectors (BPs)
    Vector2 historyBP = {355, 400};
    Vector2 windLevelBP = {355, 270};
    Vector2 angleLevelBP = {485, 270};
    Vector2 exitBP = {10, 490};
    Vector2 backBP = {10, 490};

    //Define button bounds (BBs)
    Rectangle historyBB = {historyBP.x, historyBP.y, 250, 40};
    Rectangle windLevelBB = {windLevelBP.x, windLevelBP.y, 120, 120};
    Rectangle angleLevelBB = {angleLevelBP.x, angleLevelBP.y, 120, 120};
    Rectangle exitBB = {exitBP.x, exitBP.y, 40, 40};
    Rectangle backBB = {backBP.x, backBP.y, 40, 40};

    // //Confirm / Apply button and default tank speed
    // Rectangle confirmButton = {screenWidth/2+120, screenHeight/2-170, 80, 40};
    // int speed = 1;

    // //Setting up array to store entered speed 
    // char inputArray[MAX_CHARS + 1] = {speed + '0', '\0'}; //Default value displayed
    // int charCount = 0;
    // Rectangle textBox = {screenWidth/2-100, screenHeight/2-170, 200, 40};

    // //Animate button and default projectile position
    // Rectangle animateButton = {screenWidth/2+220, screenHeight/2-170, 120, 40};
    // bool animating = false;
    // Vector2 projectilePosition = {0, 0};

    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose() && !quitFlag)        // Detect window close button or ESC key or set quitFlag to true
    {
        switch(currState) {
            case TITLE: {
                frameCounter++;
                currState = (frameCounter / targetFPS >= titleScreenTime) ? MAIN_MENU : TITLE; //If we've been at title for 4 seconds, switch to main menu
            } break;

            case MAIN_MENU: {
                if (CheckCollisionPointRec(GetMousePosition(), exitBB) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
                    quitFlag = true;
                } else if (CheckCollisionPointRec(GetMousePosition(), windLevelBB) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
                    currState = WIND_LEVEL;
                } else if (CheckCollisionPointRec(GetMousePosition(), angleLevelBB) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
                    currState = ANGLE_LEVEL;
                } else if (CheckCollisionPointRec(GetMousePosition(), historyBB) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
                    currState = HISTORY;
                }
            } break;

            case ANGLE_LEVEL: {
                if (CheckCollisionPointRec(GetMousePosition(), backBB) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
                    currState = MAIN_MENU;
                }
            } break;

            case WIND_LEVEL: {
                if (CheckCollisionPointRec(GetMousePosition(), backBB) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
                    currState = MAIN_MENU;
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
                if (CheckCollisionPointRec(GetMousePosition(), backBB) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
                    currState = MAIN_MENU;
                }
            } break;

            case SIMULATION: {
                //
            } break;

            default: {
                //shouldn't get here, means we're in an undefined state
            } break;
        }



        // //Only animate projectile IF animating currently
        // if (animating) {
        //     projectilePosition.x++;
        //     projectilePosition.y++;
        //     if (projectilePosition.y >=500) animating = false; //location of line, alternatively could detect collision
        // } 

        // //Check if mouse is over box; capture numbers
        // if (CheckCollisionPointRec(GetMousePosition(), textBox)){
            
        //     int key = GetCharPressed();

        //     // Check if more characters have been pressed on the same frame
        //     while (key > 0)
        //     {
        //         if ((key >= 48) && (key <= 57) && (charCount < MAX_CHARS))
        //         {
        //             inputArray[charCount] = (char)key;
        //             inputArray[charCount+1] = '\0'; // Add null terminator at the end of the string.
        //             charCount++;
        //         }

        //         key = GetCharPressed();  // Check next character in the queue
        //     }

        //     if (IsKeyPressed(KEY_BACKSPACE)){
        //         charCount--;
        //         if (charCount < 0) charCount = 0;
        //         inputArray[charCount] = '\0';
        //     } else if (IsKeyPressed(KEY_H)) { //H resets tank to center in case you lose it lol. Still need cursor on box though
        //         x = screenWidth/2 - 80;
        //         y = screenHeight/2;
        //     }
        // }

        // //Check if apply is clicked
        // if (CheckCollisionPointRec(GetMousePosition(), confirmButton) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
        //     speed = atoi(inputArray); //Safe because array can only ever contain digits 0-9
        // }

        // //Check if animate is clicked
        // if (CheckCollisionPointRec(GetMousePosition(), animateButton) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
        //     animating = true;
        //     projectilePosition.x = screenWidth/2 - 80;
        //     projectilePosition.y = screenHeight/2;
        // }

        // //Move to right or left
        // if (IsKeyDown(KEY_A)) x-=speed;
        // else if (IsKeyDown(KEY_D)) x+=speed;

        // //Move up or down
        // if (IsKeyDown(KEY_W)) y-=speed;
        // else if (IsKeyDown(KEY_S)) y+=speed;

        
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

            if (currState != TITLE && currState != MAIN_MENU){
                DrawTexture(backButton_T, backBP.x, backBP.y, WHITE);
            }

            switch(currState) {
                case TITLE: {
                    DrawTexture(titleScreenLogo_T, 0, 0, WHITE);

                    if (frameCounter % targetFPS >= 0 && frameCounter % targetFPS < 15){
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
            // //Draw tank
            // DrawTexture(sprite, x, y, WHITE);

            // //Show title text
            // DrawText("Tankinematics!", screenWidth/2 - 80, screenHeight/2-240, 20, DARKGREEN);
            // DrawText(TextFormat("Position: %i, %i [x, y]", x, y), screenWidth/2 - 120, screenHeight/2 - 200, 20, DARKGRAY);

            // //Speed modifier textBox, it's current value and label (to left)
            // DrawText("Speed Modifier:", textBox.x - 200, textBox.y + 8, 25, DARKGRAY);
            // DrawRectangleRec(textBox, LIGHTGRAY);
            // DrawText(inputArray, textBox.x + 5, textBox.y + 8, 25, BLACK);
            
            // //Apply button and text
            // DrawRectangleRec(confirmButton, RED);
            // DrawText("Apply", confirmButton.x + 7, confirmButton.y + 6, 25, DARKGRAY);

            // //Animate button and text
            // DrawRectangleRec(animateButton, GREEN);
            // DrawText("Animate", animateButton.x + 14, animateButton.y + 7, 25, DARKGRAY);

            // //Green line at bottom 
            // DrawLine(0, 500, 960, 505, GREEN);

            // //If animating, make projectile visible, otherwise invisible
            // if (animating) {
            //     DrawCircle(projectilePosition.x, projectilePosition.y, 10.0f, BLACK);
            // } else {
            //     DrawCircle(projectilePosition.x, projectilePosition.y, 10.0f, BLANK);
            // }

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadTexture(backButton_T);
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
