/*******************************************************************************************
*
*   Simple simulation of a projectile
*
********************************************************************************************/

#include "raylib.h"
#include <cmath>
#include<iostream>

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 840; 
    const int screenHeight = 350;

    InitWindow(screenWidth, screenHeight, "simulation");

    //Rectangle proj = {20.0f, 300.0f, 15.0f, 20.0f};

    Vector2 projectilePosition = { 20.0f, 300.0f };
    //Vector2 size = {15.0f, 20.0f};
    
    
    //int target[2] = {590, 313};
    Vector2 center = {750,200};
    //{525 , 213};
    //{750,200};
    Vector2 LineStart {0,projectilePosition.y};
    Vector2 LineEnd {screenWidth, projectilePosition.y };
    float initPos = projectilePosition.y;
    float initSpeed = 80.0f;
    float grav = 9.8f;
    double time;
    float angle = 45.0f;
    bool pause = 0;
    
    

    SetTargetFPS(80);               // Set our game to run at 60 frames-per-second
    //---------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
         
        time = GetTime();
        if (!pause)
        {
        projectilePosition.x = initSpeed*cos(angle)*time;

        projectilePosition.y =  initPos - initSpeed*sin(angle)*time + grav*time*time/2.0;
        }

        Rectangle proj = {projectilePosition.x, projectilePosition.y, 15.0f, 20.0f};
        
        // float second = initSpeed*sin(angle)*time;
        // float third = grav*time*time/2.0; 
        // printf ("time: %f\n", time);
        // printf("this is second term: %f this is third: %f \n",second, third );
         printf("position: %f, %f \n", projectilePosition.x, projectilePosition.y);

                          

        BeginDrawing();

            ClearBackground(RAYWHITE);
            DrawText("projectile simuation", 10, 10, 20, DARKGRAY);
            DrawRectangleLinesEx(proj,  10.0, RED);  

            DrawCircle(center.x, center.y, 10, GOLD );
            DrawLineV(LineStart, LineEnd, GREEN);
        if(projectilePosition.y >= LineStart.y - 15 && time != 0){
            DrawText("Not quite ...", (screenWidth/4), (screenHeight/4), 40, GRAY);
            pause = 1;
        }
        if (CheckCollisionCircleRec( center, 10, proj)){
            DrawText("Congrats!", (screenWidth/4), (screenHeight/4), 40, LIME);
            pause = 1;

        }  
                                            

        EndDrawing();

       
    
    } 

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
