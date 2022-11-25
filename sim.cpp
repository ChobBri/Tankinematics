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
#include "LvlFilter.h"
#include <random>
#include <sstream>
#include <iomanip>


Rectangle input = {960/2, 35, 100, 20};
TextBox userIn(input.x, input.y, input.width, input.height);

Simulation::Simulation(Texture2D& genericBkg_, Texture2D& tankSprite_, Texture2D& castleSprite_)
{
    genericBackground = genericBkg_;
    tankSprite = tankSprite_;
    castleSprite = castleSprite_;

    infoBox = {30, 70, 240, 90};
    tankPos = {(infoBox.x + infoBox.width)/3, 350};
    field = {0, tankPos.y+90, (float)GetScreenWidth(),(float) GetScreenHeight()}; 

    
    
}

Vector2 Simulation::getPosition (float t){
    Vector2 projectilePosition;
    if(level->angleOverVel){
        projectilePosition.x = initPos.x + speed*cos(angle * DEG2RAD)*t;
        projectilePosition.y =  initPos.y - speed*sin(angle * DEG2RAD)*t - gravity*t*t/2.0f;
    } else {
        projectilePosition.x = initPos.x + initVelX*t;
        projectilePosition.y =  initPos.y - initVelY*t - gravity*t*t/2.0f;
    }
    
    //the box
    return projectilePosition;
}

bool Simulation::targetConfirm(){
   
    if (CheckCollisionCircleRec(targetPos, 20, proj)){
        level->successfulAttempts++;
    }
    return (CheckCollisionCircleRec(targetPos, 20, proj));
}

bool Simulation:: failConfirm(){
    return proj.y > field.y+5 || proj.x > GetScreenWidth() || proj.x + proj.width < 0;
}

Rectangle Simulation:: getProj(){
    return proj;
}

Vector2 Simulation:: getTargetPos(){
    return targetPos;
}

std::string Simulation::getSolutionString(){
    std::stringstream solutionStream;
    solutionStream << std::fixed << std::setprecision(3) << level->solution;
    std::string solutionStr = solutionStream.str();

    Level::LevelType type = level->levelType;
    switch (type){
        case Level::LevelType::Gravity:
            
            return "The solution is: " + solutionStr + " m/s^2";
        case Level::LevelType::Angle:
            return "The solution is: " + solutionStr + "°";
        case Level::LevelType::InitSpeed:
            return "The solution is: " + solutionStr + " m/s";
        case Level::LevelType::InitVelX:
            return "The solution is: " + solutionStr + " m/s";
        case Level::LevelType::InitVelY:
            return "The solution is: " + solutionStr + " m/s";
    }
    return "error?";
}

void Simulation::initSimulation(levelHistory& lh, LvlFilter& lvlFilter){
    userIn.reset();
    std::vector<LevelBuilder*> possibleBuilders;
    GravityLevelBuilder glb;
    AngleLevelBuilder alb;
    SpeedLevelBuilder slb;

    InitVelXLevelBuilder xlb;
    InitVelYLevelBuilder ylb;

    bool* filters = lvlFilter.getFilters();
    if (filters[0])
        possibleBuilders.push_back(&glb);
    if (filters[1])
        possibleBuilders.push_back(&alb);
    if (filters[2])
        possibleBuilders.push_back(&xlb);
    if (filters[3])
        possibleBuilders.push_back(&ylb);
    if (filters[4])
        possibleBuilders.push_back(&slb);

    std::random_device rd;
    std::mt19937 rng(rd());

    std::uniform_int_distribution<int> intDist(0, possibleBuilders.size() - 1);

    LevelBuilder* lb = possibleBuilders[intDist(rng)];
    
    level = lh.addLevel(*(lb->BuildLevel())); //this works, and this is why (I think):
    // LevelBuilder creates a level object on the heap, then pass a copy of that object
    // to addLevel, which puts that copy in it's allLevels vector and returns a pointer 
    // to the version which exists in allLevels vector. Then pj's level pointer is refering to
    // the Level in levelHistory's allLevels vector. qed lol
    
    gravity = level->gravity;
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
    userIn.reset();

    level = lvl;
    gravity = level->gravity;
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

    std::string inputStr = userIn.getCurrentValue();
    float value;
    try {
        value = std::stof(inputStr);
    } catch(std::invalid_argument& e) {
        userIn.reset();
        return;
    }

    Level::LevelType type = level->levelType; 
    switch (type){
    case 0:
        gravity = value;
        break;
    case 1:
        angle = value;
        break;
    case 2:
        speed = value;
        break;
    case 3:
        initVelX = value;
        break;
    case 4:
        initVelY = value;
    }

    acTime = 0.0f;
    isSimulating = true;
    proj.x = initPos.x;
    proj.y = initPos.y;
    level->totalAttempts++;
    userIn.reset();
}

void Simulation::resetSimulation(){
    acTime = 0.0f;
    isSimulating = false;
    proj.x = initPos.x;
    proj.y = initPos.y;
    userIn.reset();
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
    } else {
        userIn.captureText();
    }

        // cout << gravity << endl; was this for debug?
}


void Simulation::display(){
    const char* inputW;

    string firstInfo;
    string secInfo;
    const int screenWidth = GetScreenWidth();
    //const int screenHeight = GetScreenHeight();

    DrawTexture(genericBackground, 0, 0, WHITE);
    
    std::stringstream spdStream;
    spdStream << std::fixed << std::setprecision(3) << speed;
    std::string speedStr = spdStream.str();

    std::stringstream angStream;
    angStream << std::fixed << std::setprecision(3) << angle;
    std::string angleStr = angStream.str();

    std::stringstream gravStream;
    gravStream << std::fixed << std::setprecision(3) << gravity;
    std::string gravStr = gravStream.str();

    std::stringstream initVelXStream;
    initVelXStream << std::fixed << std::setprecision(3) << initVelX;
    std::string initVelXStr = initVelXStream.str();

    std::stringstream initVelYStream;
    initVelYStream << std::fixed << std::setprecision(3) << initVelY;
    std::string initVelYStr = initVelYStream.str();

    Level::LevelType type = level->levelType; 
    switch (type){
        case 0:
            inputW = "Gravity:";
            if (level->angleOverVel){
                
                firstInfo = "Speed: " + speedStr + "m/s";
                secInfo = "Angle: "+ angleStr + "°";
            } else {
                firstInfo = "InitVelX: " + initVelXStr + "m/s";
                secInfo = "InitVelY: "+ initVelYStr + "m/s";
            }
            
            break;
        case 1:
            inputW = "Angle:";
            firstInfo = "Gravity: " + gravStr + "m/s^2";
            secInfo = "Speed: "+ speedStr + "m/s";
            break;
        case 2:
            inputW = "InitSpeed:";
            firstInfo = "Gravity: " + gravStr + "m/s^2";
            secInfo = "Angle: "+ angleStr + "°";
            break;
        case 3:
            inputW = "InitVelX:";
            firstInfo = "Gravity: " + gravStr + "m/s^2";
            secInfo = "InitVelY: "+ initVelYStr + "m/s";
            break;
        case 4:
            inputW = "InitVelY:";
            firstInfo = "Gravity: " + gravStr + "m/s^2";
            secInfo = "InitVelX: "+ initVelXStr + "m/s";
            break;
        }
        
    
    DrawRectangleRec(field, ColorFromHSV(134, 0.38, 0.41)); 
    DrawTextureV(tankSprite, tankPos, WHITE);
    DrawTexture(castleSprite,670, 145, WHITE);
    
    DrawCircleV (targetPos, 20, RED);
    
    std::stringstream distStream;
    distStream << std::fixed << std::setprecision(3) << (targetPos.x - initPos.x);
    std::string distStr = distStream.str();

    std::stringstream heightStream;
    heightStream << std::fixed << std::setprecision(3) << (initPos.y - targetPos.y);
    std::string heightStr = heightStream.str();
    //finding pixels, not sure if this is accurate to solving the problem
    string distance = "Horizontal Displacement: " + distStr + "m";
    string height = "Height: " + heightStr + "m";
    
   const char* dist = &distance[0];
   const char* tall = &height[0];
    
    DrawText(dist,screenWidth/3, tankPos.y+95,25, WHITE);
    DrawText(tall,screenWidth/3, tankPos.y+120,25, WHITE);

    
    
    DrawRectangleRec(infoBox, ColorFromHSV(55, 0.23, 0.97));
    DrawText(&firstInfo[0],infoBox.x+20, infoBox.y+20, 19, BLACK);
    DrawText(&secInfo[0],infoBox.x+20, infoBox.y+50, 19, BLACK);

    if(!isSimulating){
       
        DrawText(inputW, input.x -120, input.y, 25, WHITE);
        userIn.drawBox();
       
    }

    if(isSimulating) DrawRectangleLinesEx(proj,  10.0, RED);
    
    
    //DrawText("Not quite ...", (screenWidth/3), (screenHeight/3), 40, BLACK);
}



