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

    //Backgrounds
    Texture2D titleScreenLogo_T = LoadTexture("resources/titleScreenLogo.png");
    Texture2D genericDarkenedBackground_T = LoadTexture("resources/genericDarkenedBackground.png");
    Texture2D mainMenuBackground_T = LoadTexture("resources/mainMenuBackground.png");

    //Textures for simulation
    Texture2D tankSprite = LoadTexture("resources/tankSprite.png");
    Texture2D target = LoadTexture("resources/Target.png");
    Texture2D castle = LoadTexture("resources/castle.png");
    Texture2D damaged = LoadTexture("resources/damaged.png");

    //Buttons
    Button backButton = Button(10, 490, 40, 40, "resources/backButton.png");
    Button historyButton = Button(355, 400, 250, 40, "resources/historyButton.png");
    Button playButton = Button(355, 270, 120, 120, "resources/playButton.png");
    Button filterButton = Button(485, 270, 120, 120, "resources/filterButton.png");
    Button exitButton = Button(10, 490, 40, 40, "resources/exitButton.png");
    Button replayButton = Button(410, 250, 60, 60, "resources/Replay.png");
    Button mainMenuButton = Button(510, 250, 60, 60, "resources/main.png");
    Button hintButton = Button(900, 10, 40, 40, "resources/HINT.png");
    Button simulateButton = Button(screenWidth/2.5+20, 70, 120, 40, "resources/simulate.png");
    Button nextLevelButton = Button(screenWidth/2-46, 323, 93, 63, "resources/nextLevel.png");



    //STILL NEEED TO SWAP OVER.
    Vector2 gravityBP = {50, screenHeight/7};
    Vector2 angleBP = {50, 2*screenHeight/7};
    Vector2 velocityXBP = {50, 3*screenHeight/7};
    Vector2 velocityYBP = {50, 4*screenHeight/7};
    Vector2 speedBP = {50, 5*screenHeight/7};  


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

    //hints

    Vector2 circHint = {screenWidth/2, screenHeight/2};


    //simulation class initialized 
    Simulation pj(genericDarkenedBackground_T,tankSprite, castle);



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
                if (exitButton.isClicked()){ //Exit Button Clicked
                    globals::quitFlag = true;
                } else if (playButton.isClicked()){ //Play button clicked
                    pj.initSimulation(levelHistObj, lf);
                    globals::setCurrentState(globals::Simulation);
                } else if (filterButton.isClicked()){ //Filter button Clicked
                    globals::setCurrentState(globals::LevelFilter);
                } else if (historyButton.isClicked()){ //History button clicked
                    globals::setCurrentState(globals::History);
                }
            } break;

            case globals::LevelFilter: {
                if (backButton.isClicked()){ //Back button clicked
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
                if (replayButton.isClicked()){ //replay button clicked
                    globals::setCurrentState(globals::Simulation);
                } else if (mainMenuButton.isClicked()) {
                    globals::setCurrentState(globals:: MainMenu);
                } else if (nextLevelButton.isClicked()){
                    globals::setCurrentState(globals::Simulation);
                    pj.initSimulation(levelHistObj, lf);
                }

            } break;

            case globals::History: {
                if (backButton.isClicked()){ //Back button clicked
                    globals::setCurrentState(globals::MainMenu);
                }

                //User wants to replay a level
                if (historyListView.isClicked() != -1){ 
                    levelHistObj.moveToTop(historyListView.isClicked());

                    Level* level = historyListView.getClicked();
                    
                    pj.initSimulation(level);
                    
                    //levelHistObj.moveToTop(historyListView.isClicked());
                    globals::setCurrentState(globals::Simulation);
                }

            } break;

            case globals::Simulation: {
                pj.update();
                if (!pj.simulating())
                {
                    if (backButton.isClicked()){ //Back button clicked
                        globals::setCurrentState(globals::MainMenu);
                    }
                    else if (hintButton.isClicked()){
                        globals::setCurrentState(globals::Hints);
                    }
                    else if (simulateButton.isClicked() || IsKeyPressed(KEY_ENTER)){
                        pj.playSimulation();
                    }
                }
                else
                {
                    if (backButton.isClicked()){ //Back button clicked
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
                if (backButton.isClicked()){ //Back button clicked
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

                    playButton.drawButton();
                    filterButton.drawButton();
                    historyButton.drawButton();
                    exitButton.drawButton();

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

                    backButton.drawButton();
                } break;
                
                case globals::Success: {
                    DrawTexture(genericDarkenedBackground_T, originVector.x, originVector.y, WHITE);

                    DrawText("SUCCESS!", screenWidth/2 - 100, screenHeight/2 -  100, 50, WHITE);
                    DrawRectangleRec(field, ColorFromHSV(134, 0.38, 0.41));
                    DrawTextureV(tankSprite, tankPos, WHITE);
                    DrawTextureV(tankSprite, tankPos, WHITE); 

                    //castle moves, fix later
                    DrawTexture(damaged,670+12, 145, WHITE);
                    DrawCircleV (pj.getTargetPos(), 20, RED);

                    mainMenuButton.drawButton();
                    replayButton.drawButton();
                    nextLevelButton.drawButton();
                } break;

                case globals::History: {
                    DrawTexture(genericDarkenedBackground_T, originVector.x, originVector.y, WHITE);

                    backButton.drawButton();

                    historyListView.DrawListView();
                } break;

                case globals::Simulation: {
                    pj.display();
                    backButton.drawButton();
                    if (!pj.simulating()){
                        hintButton.drawButton();
                        simulateButton.drawButton();
                    }
                } break;

                case globals :: Hints: {
                    DrawTexture(genericDarkenedBackground_T, originVector.x, originVector.y, WHITE);

                    DrawCircleV(circHint, 200, GOLD);
                    backButton.drawButton();
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
    UnloadTexture(titleScreenLogo_T);
    UnloadTexture(genericDarkenedBackground_T);
    UnloadTexture(mainMenuBackground_T);
    UnloadTexture(tankSprite);
    UnloadTexture(target);
    UnloadTexture(castle);
    UnloadTexture(damaged);
    //Save levels back to the disk
    PersistentData::saveLevels(levelHistObj.allLevels);

    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
