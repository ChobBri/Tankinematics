/*******************************************************************************************
*
*   Simple simulation of a projectile
*
********************************************************************************************/

#include "raylib.h"
#include <cmath>
#include <iostream>
#include "sim.h"

Simulation::Simulation(Texture2D& genericBkg_, Texture2D& tankSprite_, Texture2D& castleSprite_, Texture2D& simSprite_, Texture2D& hintSprite_, Texture2D& backBSprite_)
{
    genericBackground = genericBkg_;
    tankSprite = tankSprite_;
    castleSprite = castleSprite_;
    simulationSprite = simSprite_;
    hintSprite = hintSprite_;
    backButtonSprite = backBSprite_;

    infoBox = {30, 70, 240, 90};
    tankPos = {(infoBox.x + infoBox.width)/3, 350};
    field = {0, tankPos.y+90, (float)GetScreenWidth(),(float) GetScreenHeight()}; 
}

Vector2 Simulation::getPosition (float t){
    Vector2 projectilePosition;
    projectilePosition.x = initPos.x + speed*cos(angle)*t;
    projectilePosition.y =  initPos.y - speed*sin(angle)*t + gravity*t*t/2.0f;
    //the box
    return projectilePosition;
}

bool Simulation::targetConfirm(int lineY, Vector2 targetLoc){
    if (proj.y > lineY+10){
        return false;
    }

    return (CheckCollisionCircleRec(targetLoc, 20, proj));
}

bool Simulation:: failConfirm(int lineY){
    if (proj.y > lineY+5){
        return true;
    }
    else{
        return false;
    }
}

Rectangle Simulation:: getProj(){
    return proj;
}

void Simulation::initSimulation(){
    gravity = 9.8f;
    angle = 45.0f;
    speed = 80.0f;
    initPos = {240.0f, 350.0f};
    acTime = 0.0f;
    proj = {initPos.x, initPos.y, 15.0f, 20.0f};
    int rand = GetRandomValue(20,200);
    targetPos = {720, initPos.y - rand};

}

void Simulation::initSimulation(Level* lvl){
    gravity = 9.8f;
    angle = 45.0f;
    speed = 80.0f;
    initPos = {240.0f, 350.0f};
    acTime = 0.0f;
    proj = {initPos.x, initPos.y, 15.0f, 20.0f};
    int rand = GetRandomValue(20,200);
    targetPos = {720, initPos.y - rand};

    
}

void Simulation::playSimulation(){
    acTime = 0.0f;
    isSimulating = true;
}

bool Simulation::simulating(){
    return isSimulating;
}

void Simulation::update()
{
    Vector2 backBP = {10, 490};
    Vector2 hintBP = {900, 10};
    Vector2 simulateBP = {GetScreenWidth()/2.5f+20, 70};

    Rectangle backBB = {backBP.x, backBP.y, 40, 40};
    Rectangle hintBB = {hintBP.x, hintBP.y, 40,40};
    Rectangle simulateBB = {simulateBP.x, simulateBP.y, 120, 40};

    if (isSimulating){
        acTime += GetFrameTime();
        Vector2 projectilePosition = getPosition(acTime);
        proj = {projectilePosition.x, projectilePosition.y, 15, 20};

        // if (targetConfirm(field.y, targetPos)) globals::flag =1;

        // if (pj.failConfirm(field.y)){
        //     DrawText("Not quite ...", (screenWidth/3), (screenHeight/3), 40, BLACK);
        //     globals:: pause = 1;
        // }
    } else {
        
    }
}

void Simulation::display(){
    const int screenWidth = GetScreenWidth();
    const int screenHeight = GetScreenHeight();

    DrawTexture(genericBackground, 0, 0, WHITE);

    
    DrawRectangleRec(field, ColorFromHSV(134, 0.38, 0.41)); 
    DrawTextureV(tankSprite, tankPos, WHITE);
    DrawTexture(castleSprite,670, 145, WHITE);
    //DrawTexture(target, 720, tankPos.y-rand, RED);
    DrawCircleV (targetPos, 20, RED);
    
    char distance[] = {"Distance: 60km"};
    char height[] = {"Height: 50km"};
    char infoGrav[] = {"Gravity: 9.8m/s^2"};
    char infoInitVel[] = {"Initial Velocity: 30 m/s"};
    DrawText(distance,screenWidth/3, tankPos.y+95,25, WHITE);
    DrawText(height,screenWidth/3+200, tankPos.y+95,25, WHITE);

    //placeholder for input
    DrawRectangleRec(infoBox, ColorFromHSV(55, 0.23, 0.97));
    DrawText(infoGrav,infoBox.x+20, infoBox.y+20, 19, BLACK);
    DrawText(infoInitVel,infoBox.x+20, infoBox.y+50, 19, BLACK);

    if(!isSimulating){
        Rectangle input = {(float)screenWidth/2, 35, 100, 20};
        char inputW[] = {"Angle: "};
        DrawText(inputW, input.x -80, input.y, 25, WHITE);
        DrawRectangleRec(input, WHITE);
    }

    Vector2 backBP = {10, 490};
    Vector2 hintBP = {900, 10};
    Vector2 simulateBP = {screenWidth/2.5f+20, 70};
    
    if(!isSimulating){
        DrawTexture(simulationSprite, simulateBP.x, simulateBP.y, WHITE);
        DrawTexture(hintSprite, hintBP.x, hintBP.y, WHITE);
    }
    DrawTexture(backButtonSprite, backBP.x, backBP.y, WHITE);

    if(isSimulating) DrawRectangleLinesEx(proj,  10.0, RED);
    
    //DrawText("Not quite ...", (screenWidth/3), (screenHeight/3), 40, BLACK);
}

// void simulation::drawSim(){

//     Vector2 position = getPosition(initPos);
//     BeginDrawing();

          
//         DrawRectangleLinesEx(proj,  10.0, RED);                                 

//         EndDrawing();
// }

// //------------------------------------------------------------------------------------
// // Program main entry point
// //------------------------------------------------------------------------------------
// int main(void)
// {
//     // Initialization
//     //--------------------------------------------------------------------------------------
//     const int screenWidth = 840; 
//     const int screenHeight = 350;

       

//     InitWindow(screenWidth, screenHeight, "simulation");
//     // could replace this with the level builder output 
//     Vector2 projectilePosition = { 20.0f, 300.0f };

//     //target coordinates
//     Vector2 center = {525 , 213};
//     //{750,200};
//     //for the terrain
//     Vector2 LineStart {0,projectilePosition.y};
//     Vector2 LineEnd {screenWidth, projectilePosition.y };
//     float initPos = projectilePosition.y;

//     //everything else can be replaced by the physicsworld 
//     float initSpeed = 80.0f;
//     float grav = 9.8f;
//     double time;
//     float angle = 45.0f;
//     bool pause = 0;
   
    

//     SetTargetFPS(80);               // Set our game to run at 80 frames-per-second
//     //---------------------------------------------------------------------------------------

//     // Main game loop
//     while (!WindowShouldClose())    // Detect window close button or ESC key
//     {
//         /**
//          * update
//          */ 
//         time = GetTime();
//         if (!pause)
//         {
//         projectilePosition.x = initSpeed*cos(angle)*time;

//         projectilePosition.y =  initPos - initSpeed*sin(angle)*time + grav*time*time/2.0;
//         }

//         Rectangle proj = {projectilePosition.x, projectilePosition.y, 15.0f, 20.0f};
        
//        //for testing
//          printf("position: %f, %f \n", projectilePosition.x, projectilePosition.y);   

//         BeginDrawing();

//             ClearBackground(RAYWHITE);
//             DrawText("projectile simuation", 10, 10, 20, DARKGRAY);
//             DrawRectangleLinesEx(proj,  10.0, RED);  

//             DrawCircle(center.x, center.y, 10, GOLD );
//             DrawLineV(LineStart, LineEnd, GREEN);
//         /*
//         could have new windows pop up
//         */
       
//         //checking if projectile hit the terrain
//         if(projectilePosition.y >= LineStart.y - 15 && time != 0){
//             DrawText("Not quite ...", (screenWidth/4), (screenHeight/4), 40, GRAY);
//             pause = 1;
//         }
//         //checking if projectile hit target
//         if (CheckCollisionCircleRec( center, 10, proj)){
//             DrawText("Congrats!", (screenWidth/4), (screenHeight/4), 40, LIME);
//             pause = 1;

//         }  
                                            

//         EndDrawing();

       
    
//     } 

//     // De-Initialization
//     //--------------------------------------------------------------------------------------
//     CloseWindow();        // Close window and OpenGL context
//     //--------------------------------------------------------------------------------------

//     return 0;

