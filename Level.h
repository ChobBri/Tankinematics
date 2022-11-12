#ifndef LEVEL_H
#define LEVEL_H

#include "raylib.h"
#include <string>
#include <vector>

/**
 * Level represents the context of a level.
 * 
 * It contains the minimum amount of data to represent a level.
*/


struct Level 
{
    enum LevelType {Gravity = 0, Angle, InitSpeed, InitVelX, InitVelY};
    float gravity = 0.0f;
    float angle = 0.0f;
    float initSpeed = 0.0f;
    Vector2 initVelocity = {0.0f, 0.0f};
    Vector2 tankPosition = {0.0f, 0.0f};
    Vector2 targetPosition = {0.0f, 0.0f};
    std::vector<std::string> hints;  // Text to provide hint to user. There can be multiple hints
    std::string solution;  // Text to provide solution to user
    bool angleOverVel = true;  // Flag to determine whether to solve for angle or velocity
    int totalAttempts = 0;
    int successfulAttempts = 0;
    float time = 0.0f; // in seconds
    LevelType levelType = LevelType::Gravity;
};

bool isEqual(Level lvl1, Level otherLvl){
    return (lvl1.gravity == otherLvl.gravity && lvl1.angle == otherLvl.angle && lvl1.initSpeed == otherLvl.initSpeed
    && lvl1.tankPosition.x == otherLvl.tankPosition.x && lvl1.tankPosition.y == otherLvl.tankPosition.y && 
    lvl1.targetPosition.x == otherLvl.targetPosition.x && lvl1.targetPosition.y == otherLvl.targetPosition.y);
}
#endif