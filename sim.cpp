/*******************************************************************************************
*
*   Simple simulation of a projectile
*
********************************************************************************************/

#include "raylib.h"
#include <cmath>
#include <iostream>
#include "sim.h"

simulation::simulation(int width, int height, float gravi, float ang, float initvel, Vector2 init){
    screenWidth = width;
    screenHeight = height;

    //placeholders
    grav = gravi;
    angle  = ang;
    initVel = initvel;
    initPos = init;
    acTime = 0;
    //initial position
    proj = {init.x, init.y, 15, 20};
    
}

Vector2 simulation::getPosition (Vector2 projectilePosition){
    acTime += GetFrameTime();
    projectilePosition.x = initPos.x + initVel*cos(angle)*acTime;
    projectilePosition.y =  initPos.y - initVel*sin(angle)*acTime + grav*acTime*acTime/2.0;
    //the box
    proj = {projectilePosition.x, projectilePosition.y, 15, 20};
    return projectilePosition;
}

bool simulation::targetConfirm(int lineY, Vector2 targetLoc){
    if (proj.y > lineY+10){
        return false;
    }

    return (CheckCollisionCircleRec(targetLoc, 20, proj));

}

bool simulation:: failConfirm(int lineY){
    if (proj.y > lineY+5){
        return true;
    }
    else{
        return false;
    }
}

Rectangle simulation:: getProj(){
    return proj;
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

