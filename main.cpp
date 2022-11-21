/*******************************************************************************************
*
*   Team Jasper (20) Basic Framework
*
********************************************************************************************/


#include "raylib.h"

#include "PersistentData.hpp"
#include "sim.h"
#include "TextBox.hpp"
#include "ListView.hpp"
#include "lvlHistory.h"
#include "button.h"
#include "lvlFilter.h"

#include <string.h>
#include <stdlib.h>
#include <iostream>


namespace globals {
        enum gameStates {Title = 0, MainMenu, LevelFilter, Success, History, Simulation, Hints};
        static gameStates currentState = Title;
        static bool quitFlag = false; //Setting to true will close game
        int frameCounter = 0; //Currently only used to stay on title screen for specified number of frames

        //for simulation
        int flag = 0;
        bool pause = 0;
        int simCheck = 0;
        Level simulationArgument;

        void setCurrentState(globals::gameStates newState){
            globals::currentState = newState;
            return;
        }
}

int main(void)
{   

    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 1920/2; //Keep that gorgeous 16:9 ratio 
    const int screenHeight = 1080/2;
    const int targetFPS = 60; //BE CAREFUL IF CHANGING: this value is used in calculating time delays, for animations, etc.
    const int titleScreenTime = 2; 
    const Vector2 originVector = {0, 0}; //Frequently used position in debugging

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

    //for sim
    Texture2D tankSprite = LoadTexture("resources/tankSprite.png");
    Texture2D target = LoadTexture("resources/Target.png");
    Texture2D hint = LoadTexture("resources/HINT.png");
    Texture2D simulate = LoadTexture("resources/simulate.png");
    Texture2D castle = LoadTexture("resources/castle.png");
    Texture2D damaged = LoadTexture("resources/damaged.png");

    //for success
    Texture2D replay = LoadTexture("resources/Replay.png");
    Texture2D main = LoadTexture("resources/main.png");

    //Define button placement vectors (BPs). BPs are used to define where to draw textures which overlay onto rectangles. 
    Vector2 historyBP = {355, 400};
    Vector2 playBP = {355, 270};
    Vector2 filterBP = {485, 270};
    Vector2 exitBP = {10, 490};
    Vector2 backBP = {10, 490};

    Vector2 hintBP = {900, 10};
    Vector2 simulateBP = {screenWidth/2.5+20, 70};

    Vector2 replayBP = {410, 250};
    Vector2 mainBP = {510, 250};

    // Define level filter buttons (gravity, angle, x velocity, y velocity, speed)
    Vector2 gravityBP = {50, screenHeight/7};
    Vector2 angleBP = {50, 2*screenHeight/7};
    Vector2 velocityXBP = {50, 3*screenHeight/7};
    Vector2 velocityYBP = {50, 4*screenHeight/7};
    Vector2 speedBP = {50, 5*screenHeight/7};   


    //Define button bounds (BBs)
    //Rectangles which are under their respective textures. Done this way so you can use intersection-detection methods which use rectangles and points. 
    Rectangle historyBB = {historyBP.x, historyBP.y, 250, 40};
    Rectangle playBB = {playBP.x, playBP.y, 120, 120};
    Rectangle filterBB = {filterBP.x, filterBP.y, 120, 120};
    Rectangle exitBB = {exitBP.x, exitBP.y, 40, 40};
    Rectangle backBB = {backBP.x, backBP.y, 40, 40};
    //placement of the buttons may be slightly off, have to fix
    Rectangle hintBB = {hintBP.x, hintBP.y, 40,40};
    Rectangle simulateBB = {simulateBP.x, simulateBP.y, 120, 40};
    Rectangle replayBB = {replayBP.x, replayBP.y, 60, 60};
    Rectangle mainBB = {mainBP.x, mainBP.y, 60,60};
    // Create level filter buttons
    Button toggleGravity = {gravityBP.x, gravityBP.y, 50, 50};
    toggleGravity.setState(true); // Initialize gravity field to true when game starts (need at least one field to be true)
    Button toggleAngle = {angleBP.x, angleBP.y, 50, 50};
    Button toggleVelocityX = {velocityXBP.x, velocityXBP.y, 50, 50};
    Button toggleVelocityY = {velocityYBP.x, velocityYBP.y, 50, 50};
    Button toggleSpeed = {speedBP.x, speedBP.y, 50, 50};
    

    //Define the placements for simulation -- can be replaced with calling from level builder later
    Rectangle infoBox = {30, 70, 240, 90};

    Vector2 tankPos = {(infoBox.x + infoBox.width)/3, 350};
    Rectangle field = {0, tankPos.y+90, screenWidth, screenHeight}; 


    int rand = GetRandomValue(20,200);

    //hints

    Vector2 circHint = {screenWidth/2, screenHeight/2};

    //simulation class initialized 
    Simulation pj(genericDarkenedBackground_T,tankSprite, castle, simulate, hint, backButton_T);

    ///////////////////


    //--------------------------------------------------------------------------------------

    //Create levelHistory object
    levelHistory levelHistObj = levelHistory();
    levelHistObj.allLevels = PersistentData::loadLevels();

    //Create level history view
    ListView historyListView(240, 30, 480, 480, 10, levelHistObj.allLevels);
    // Create level filter settings
    LvlFilter lf(true,false,false,false,false);

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
                    pj.initSimulation(levelHistObj);
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
                else if (CheckCollisionPointRec(GetMousePosition(), toggleGravity.getBounds()) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){ 
                    if (!toggleGravity.getState() || toggleAngle.getState() || toggleVelocityX.getState() || toggleVelocityY.getState() || toggleSpeed.getState()) {
                        lf.toggleIndex(0);
                        toggleGravity.setState(!toggleGravity.getState());
                    }
                }
                else if (CheckCollisionPointRec(GetMousePosition(), toggleAngle.getBounds()) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){ 
                    if (toggleGravity.getState() || !toggleAngle.getState() || toggleVelocityX.getState() || toggleVelocityY.getState() || toggleSpeed.getState()) {
                        lf.toggleIndex(1);
                        toggleAngle.setState(!toggleAngle.getState());
                    }
                }
                else if (CheckCollisionPointRec(GetMousePosition(), toggleVelocityX.getBounds()) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){ 
                    if (toggleGravity.getState() || toggleAngle.getState() || !toggleVelocityX.getState() || toggleVelocityY.getState() || toggleSpeed.getState()) {
                        lf.toggleIndex(2);
                        toggleVelocityX.setState(!toggleVelocityX.getState());
                    }
                }
                else if (CheckCollisionPointRec(GetMousePosition(), toggleVelocityY.getBounds()) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){ 
                    if (toggleGravity.getState() || toggleAngle.getState() || toggleVelocityX.getState() || !toggleVelocityY.getState() || toggleSpeed.getState()) {
                        lf.toggleIndex(3);
                        toggleVelocityY.setState(!toggleVelocityY.getState());
                    }
                }
                else if (CheckCollisionPointRec(GetMousePosition(), toggleSpeed.getBounds()) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){ 
                    if (toggleGravity.getState() || toggleAngle.getState() || toggleVelocityX.getState() || toggleVelocityY.getState() || !toggleSpeed.getState()) {
                        lf.toggleIndex(4);
                        toggleSpeed.setState(!toggleSpeed.getState());
                    }
                }
            } break;

            case globals::Success: {
                if (CheckCollisionPointRec(GetMousePosition(), replayBB) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){ //replay button clicked
                    globals::setCurrentState(globals::Simulation);
                }
                else if (CheckCollisionPointRec(GetMousePosition(), mainBB) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
                    globals::setCurrentState(globals:: MainMenu);
            } break;

            case globals::History: {
                if (CheckCollisionPointRec(GetMousePosition(), backBB) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){ //Back button clicked
                    globals::setCurrentState(globals::MainMenu);
                }

                //User wants to replay a level
                if (historyListView.isClicked() != -1){ 
                    pj.initSimulation(historyListView.getClicked());
                    
                    levelHistObj.moveToTop(historyListView.isClicked());
                    globals::setCurrentState(globals::Simulation);
                }

            } break;

            case globals::Simulation: {
                pj.update();
                if (!pj.simulating())
                {
                    if (CheckCollisionPointRec(GetMousePosition(), backBB) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){ //Back button clicked
                        globals::setCurrentState(globals::MainMenu);
                    }
                    else if (CheckCollisionPointRec(GetMousePosition(), hintBB) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
                        globals::setCurrentState(globals::Hints);
                    }
                    else if (CheckCollisionPointRec(GetMousePosition(), simulateBB) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
                        pj.playSimulation();
                    }
                }
                else
                {
                    if (CheckCollisionPointRec(GetMousePosition(), backBB) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){ //Back button clicked
                        pj.resetSimulation();
                        //something to return to previous state I guess, maybe level saving history or something, right now, only 1 simulation possible
                    }
                    //checking if it was a success
                    else if (pj.targetConfirm()){
                        pj.resetSimulation();
                        globals::setCurrentState(globals::Success);
                    } 
                }
            } break;

            case globals::Hints:{
                if (CheckCollisionPointRec(GetMousePosition(), backBB) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){ //Back button clicked
                    globals::setCurrentState(globals::Simulation);
                }
            }

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

                    toggleAngle.drawState();
                    toggleSpeed.drawState();
                    toggleVelocityX.drawState();
                    toggleVelocityY.drawState();
                    toggleGravity.drawState();

                    DrawText("Select parameter(s) to isolate and solve for:", 20,20, 25, WHITE);
                    DrawText("Gravity", gravityBP.x+50+50, gravityBP.y, 50, WHITE);
                    DrawText("Angle", angleBP.x+50+50, angleBP.y, 50, WHITE);
                    DrawText("Velocity (x)", velocityXBP.x+50+50, velocityXBP.y, 50, WHITE);
                    DrawText("Velocity (y)", velocityYBP.x+50+50, velocityYBP.y, 50, WHITE);
                    DrawText("Speed", speedBP.x+50+50, speedBP.y, 50, WHITE);

                    DrawTexture(backButton_T, backBP.x, backBP.y, WHITE);
                } break;
                
                case globals::Success: {
                    DrawTexture(genericDarkenedBackground_T, originVector.x, originVector.y, WHITE);

                    DrawText("SUCCESS!", screenWidth/2 - 100, screenHeight/2 -  100, 50, WHITE);
                    DrawRectangleRec(field, ColorFromHSV(134, 0.38, 0.41));
                    DrawTextureV(tankSprite, tankPos, WHITE);
                    DrawTextureV(tankSprite, tankPos, WHITE); 
                    //castle moves, fix later
                    DrawTexture(damaged,670, 145, WHITE);
                    DrawTexture(target, 720, tankPos.y-rand, RED);

                    DrawTexture(main, mainBB.x, mainBB.y, WHITE);
                    DrawTexture(replay, replayBB.x, replayBB.y, WHITE);
                } break;

                case globals::History: {
                    DrawTexture(genericDarkenedBackground_T, originVector.x, originVector.y, WHITE);

                    DrawTexture(backButton_T, backBP.x, backBP.y, WHITE);

                    historyListView.DrawListView();
                } break;

                case globals::Simulation: {
                    pj.display();
                } break;

                case globals :: Hints: {
                    DrawTexture(genericDarkenedBackground_T, originVector.x, originVector.y, WHITE);

                    DrawCircleV(circHint, 200, GOLD);
                    DrawTexture(backButton_T, backBP.x, backBP.y, WHITE);
                    DrawText("Hints", screenWidth/2-40, 80, 40, BLACK);
                    //placeholder
                    DrawText("Use the Equation: --------", screenWidth/2 - 160, 250,25, BLACK);
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
    //Free up memory used to store textures
    UnloadTexture(backButton_T); 
    UnloadTexture(titleScreenLogo_T);
    UnloadTexture(genericDarkenedBackground_T);
    UnloadTexture(mainMenuBackground_T);
    UnloadTexture(historyButton_T);
    UnloadTexture(playButton_T);
    UnloadTexture(filterButton_T);
    UnloadTexture(exitButton_T);
    UnloadTexture(tankSprite);
    UnloadTexture(target);
    UnloadTexture(hint);
    UnloadTexture(simulate);
    UnloadTexture(castle);
    UnloadTexture(damaged);
    UnloadTexture(replay);
    UnloadTexture(main);

    //Save levels back to the disk
    PersistentData::saveLevels(levelHistObj.allLevels);

    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
