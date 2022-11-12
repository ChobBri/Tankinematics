#ifndef GRAVITYLEVELBUILDER_H
#define GRAVITYLEVELBUILDER_H

#include "LevelBuilder.h"
#include "LevelConstraints.h"
#include "Level.h"
#include <random>
#include <vector>
#include <string>

/**
 * GravityLevelBuilder is an abstract class to represent a level builder for gravity levels.
*/
class GravityLevelBuilder : public LevelBuilder
{
public:
    Level* BuildLevel() override
    {
        Level* level = new Level();

        // Initialize level construction
        initConstruct(level);

        // Set level type
        level->levelType = Level::LevelType::Gravity;

        // Different build method depending on angleOverVel
        if (level->angleOverVel)
        {
            // Set hints
            std::vector<std::string> hints = {"do this", "try that", "how bout this"};
            level->hints = hints;

            // Solve for solution
            float ang = level->angle;
            Vector2 iVel = {level->initSpeed * cosf(ang * DEG2RAD), level->initSpeed * sinf(ang * DEG2RAD)};

            float dx = level->targetPosition.x - level->tankPosition.x;
            float t = dx/(iVel.x);
            float dy = level->targetPosition.y - level->tankPosition.y;
            float a = 2 * (dy - iVel.y * t) / (t*t);  // solve for gravity

            level->gravity = a;
            level->solution = "The answer is " + std::to_string(a);
        }
        else
        {
            // Set hints
            std::vector<std::string> hints = {"do this", "try that", "how bout this"};
            level->hints = hints;

            // Solve for solution
            float dx = level->targetPosition.x - level->tankPosition.x;
            float t = dx/(level->initVelocity.x);
            float dy = level->targetPosition.y - level->tankPosition.y;
            float a = 2 * (dy - level->initVelocity.y * t)/(t*t);  // solve for gravity

            level->gravity = a;
            level->solution = "The answer is " + std::to_string(a);
        }
        
        return level;
    }
};

#endif

// Example of when mixed with polymorphism
/**
 * 
 *    std::vector<LevelBuilder*> v;

    for (size_t i = 0; i < 3; i++)
    {
        GravityLevelBuilder* builder = new GravityLevelBuilder();
        v.push_back(builder);
    }

    for (size_t i = 0; i < v.size(); i++)
    {
        Level* l = v[i]->BuildLevel();
        std::cout << l->angle << " " << l->gravity << l->hints[0] << l->hints[1] << l->hints[2] << std::endl;
        delete l;
        delete v[i];
    }
 * 
*/