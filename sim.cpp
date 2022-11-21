/*******************************************************************************************
*
*   Simple simulation of a projectile
*
********************************************************************************************/

#include "raylib.h"
#include <cmath>
#include <iostream>
#include "sim.h"
#include "GravityLevelBuilder.h"
#include "AngleLevelBuilder.h"
#include "SpeedLevelBuilder.h"
#include "InitVelXLevelBuilder.h"
#include "InitVelYLevelBuilder.h"
#include "lvlHistory.h"
#include "level.h"
#include <string>
#include "TextBox.hpp"


Rectangle input = {960/2, 35, 100, 20};
TextBox userIn(input.x, input.y, input.width, input.height);

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
    input = {(float)GetScreenWidth()/2, 35, 100, 20};
    
    
}

Vector2 Simulation::getPosition (float t){
    Vector2 projectilePosition;
    if(level->angleOverVel){
        projectilePosition.x = initPos.x + speed*cos(angle * DEG2RAD)*t;
        projectilePosition.y =  initPos.y - speed*sin(angle * DEG2RAD)*t + gravity*t*t/2.0f;
    } else {
        projectilePosition.x = initPos.x + initVelX*t;
        projectilePosition.y =  initPos.y - initVelY*t + gravity*t*t/2.0f;
    }
    
    //the box
    return projectilePosition;
}

bool Simulation::targetConfirm(){
    if (proj.y > field.y+10){
        return false;
    }
    if (CheckCollisionCircleRec(targetPos, 20, proj)){
        level->successfulAttempts++;
    }
    return (CheckCollisionCircleRec(targetPos, 20, proj));
}

bool Simulation:: failConfirm(){
    return proj.y > field.y+5;
}

Rectangle Simulation:: getProj(){
    return proj;
}

void Simulation::initSimulation(levelHistory& lh){
     GravityLevelBuilder lb;
    // AngleLevelBuilder lb;
    // SpeedLevelBuilder lb;

    // InitVelXLevelBuilder lb;
    // InitVelYLevelBuilder lb;

    
    level = lh.addLevel(*lb.BuildLevel()); //this works, and this is why (I think):
    // LevelBuilder creates a level object on the heap, then pass a copy of that object
    // to addLevel, which puts that copy in it's allLevels vector and returns a pointer 
    // to the version which exists in allLevels vector. Then pj's level pointer is refering to
    // the Level in levelHistory's allLevels vector. qed lol
    
    gravity = -level->gravity;
    angle = level->angle;
    speed = level->initSpeed;
    initVelX = level->initVelocity.x;
    initVelY = level->initVelocity.y;
    initPos = {240.0f, 350.0};  // treat this as the offset to level data
    acTime = 0.0f;
    proj = {initPos.x, initPos.y, 15.0f, 20.0f};
    targetPos = {initPos.x + level->targetPosition.x, initPos.y - level->targetPosition.y};

}

void Simulation::initSimulation(Level* lvl){
    level = lvl;
    gravity = -level->gravity;
    angle = level->angle;
    speed = level->initSpeed;
    initVelX = level->initVelocity.x;
    initVelY = level->initVelocity.y;
    initPos = {240.0f, 350.0};  // treat this as the offset to level data
    acTime = 0.0f;
    proj = {initPos.x, initPos.y, 15.0f, 20.0f};
    targetPos = {initPos.x + level->targetPosition.x, initPos.y - level->targetPosition.y};
  
}

void Simulation::playSimulation(){
    acTime = 0.0f;
    isSimulating = true;
    proj.x = initPos.x;
    proj.y = initPos.y;
    level->totalAttempts++;
}

void Simulation::resetSimulation(){
    acTime = 0.0f;
    isSimulating = false;
    proj.x = initPos.x;
    proj.y = initPos.y;
}

bool Simulation::simulating(){
    return isSimulating;
}

void Simulation::update()
{
    if (isSimulating){
        acTime += GetFrameTime();
        Vector2 projectilePosition = getPosition(acTime * 3.0f);  // playing at 3 times the speed
        proj = {projectilePosition.x, projectilePosition.y, 15, 20};

        if(failConfirm()){
            isSimulating = false;
        }
    } 
    userIn.captureText();
    if(!(userIn.getCurrentValue()).empty())
    {
      Level::LevelType type = level->levelType; 
        switch (type){
        case 0:
            gravity = stof(userIn.getCurrentValue());
            break;
        case 1:
            angle = stof(userIn.getCurrentValue());
            break;
        case 2:
            speed = stof(userIn.getCurrentValue());
            break;
        case 3:
            initVelX = stof(userIn.getCurrentValue());
            break;
        case 4:
            initVelY = stof(userIn.getCurrentValue());

        }
    }
        cout << gravity << endl;
}


void Simulation::display(){
    const char* inputW;
    const char* firstInfo;
    const char* secInfo;
    string convert;
    string convertT;
    const int screenWidth = GetScreenWidth();
    const int screenHeight = GetScreenHeight();

    DrawTexture(genericBackground, 0, 0, WHITE);
    //finding level type
    Level::LevelType type = level->levelType; 
    switch (type){
        case 0:
            inputW = "Gravity:";
            convert = "Velocity: " + to_string((ceil(speed*100.0))/100.0) + "m/s";
            firstInfo = &convert[0];
            convertT = "Angle: "+ to_string((ceil(angle*100.0))/100.0) + "°";
            secInfo = &convertT[0];
            break;
        case 1:
            inputW = "Angle:";
            convert = "Gravity: " + to_string((ceil(gravity*100.0))/100.0) + "m/s";
            firstInfo = &convert[0];
            convertT = "Angle: "+ to_string((ceil(angle*100.0))/100.0) + "°";
            secInfo = &convertT[0];
            break;
        case 2:
            inputW = "InitSpeed:";
            convert = "Gravity: " + to_string((ceil(gravity*100.0))/100.0) + "m/s";
            firstInfo = &convert[0];
            convertT = "Angle: "+ to_string((ceil(angle*100.0))/100.0) + "°";
            secInfo = &convertT[0];
            break;
        case 3:
            inputW = "InitVelX:";
            convert = "Gravity: " + to_string((ceil(gravity*100.0))/100.0) + "m/s";
            firstInfo = &convert[0];
            convertT = "Angle: "+ to_string((ceil(angle*100.0))/100.0) + "°";
            secInfo = &convertT[0];
            break;
        case 4:
            inputW = "InitVelY:";
            convert = "Gravity: " + to_string((ceil(gravity*100.0))/100.0) + "m/s";
            firstInfo = &convert[0];
            convertT = "Angle: "+ to_string((ceil(angle*100.0))/100.0) + "°";
            secInfo = &convertT[0];
            break;
        }
        
    
    DrawRectangleRec(field, ColorFromHSV(134, 0.38, 0.41)); 
    DrawTextureV(tankSprite, tankPos, WHITE);
    DrawTexture(castleSprite,670, 145, WHITE);
    
    DrawCircleV (targetPos, 20, RED);
    
    //finding pixels, not sure if this is accurate to solving the problem
    string distance = "Distance: " + to_string((ceil(targetPos.x - initPos.x)))+ "m";
    string height = "Height: " + to_string(ceil(initPos.y - targetPos.y))+ "m";
    
   const char* dist = &distance[0];
   const char* tall = &height[0];
    
    DrawText(dist,screenWidth/3, tankPos.y+95,25, WHITE);
    DrawText(tall,screenWidth/3, tankPos.y+120,25, WHITE);

    
    
    DrawRectangleRec(infoBox, ColorFromHSV(55, 0.23, 0.97));
    DrawText(firstInfo,infoBox.x+20, infoBox.y+20, 19, BLACK);
    DrawText(secInfo,infoBox.x+20, infoBox.y+50, 19, BLACK);

    if(!isSimulating){
       
        DrawText(inputW, input.x -100, input.y, 25, WHITE);
        userIn.drawBox();
        
       
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



