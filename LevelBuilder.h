#ifndef LEVELBUILDER_H
#define LEVELBUILDER_H

#include "Level.h"
#include "LevelConstraints.h"
#include <random>
#include <vector>
#include <string>

/**
 * LevelBuilder is an abstract class to represent a level builder.
*/
class LevelBuilder
{
public:
    // Virtual destructor for polymorphism
    virtual ~LevelBuilder() = default;

    // Abstract function to build level
    virtual Level* BuildLevel() = 0;
protected:
    // Initializes level except for levelType, solution, and hints
    virtual void initConstruct(Level* level)
    {
        // Create random device
        std::random_device rd;
        std::mt19937 rng(rd());

        // Initialize gravity
        std::uniform_real_distribution<float> gravityDist(LevelConstraints::MIN_GRAVITY, LevelConstraints::MAX_GRAVITY);
        level->gravity = -gravityDist(rng);

        // Initialize angleOverVel
        std::uniform_real_distribution<float> zeroToOneDist(0.0f, 1.0f);
        level->angleOverVel = zeroToOneDist(rng) < 0.5f;

        // Initialize angle
        std::uniform_real_distribution<float> angleDist(LevelConstraints::MIN_ANGLE, LevelConstraints::MAX_ANGLE);
        level->angle = angleDist(rng);
        
        // Initialize initSpeed
        std::uniform_real_distribution<float> speedDist(LevelConstraints::MIN_SPEED, LevelConstraints::MAX_SPEED);
        level->initSpeed = speedDist(rng);

        // Initialize initVelocity
        Vector2 initVel = {level->initSpeed * cosf(level->angle * DEG2RAD), level->initSpeed * sinf(level->angle * DEG2RAD)};
        level->initVelocity = initVel;

        // Initialize positions
        std::uniform_real_distribution<float> posXDist(LevelConstraints::MIN_DIST_X, LevelConstraints::MAX_DIST_X);
        std::uniform_real_distribution<float> posYDist(LevelConstraints::MIN_DIST_Y, LevelConstraints::MAX_DIST_Y);
        level->tankPosition = {0.0f, 0.0f};
        level->targetPosition = {level->tankPosition.x + posXDist(rng), level->tankPosition.y + posYDist(rng)};

        // Initalize local stats
        level->totalAttempts = 0;
        level->successfulAttempts = 0;
        level->time = 0.0f;
    }
};

#endif
