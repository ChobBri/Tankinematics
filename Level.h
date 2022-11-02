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
    LevelType levelType = LevelType::Gravity;
};

#endif