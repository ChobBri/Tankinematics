#ifndef INITVELYLEVELBUILDER_H
#define INITVELYLEVELBUILDER_H

#include "LevelBuilder.h"
#include "LevelConstraints.h"
#include "Level.h"
#include <random>
#include <vector>
#include <string>

/**
 * InitVelYLevelBuilder is an abstract class to represent a level builder for initVelY levels.
*/
class InitVelYLevelBuilder : public LevelBuilder
{
public:
    Level* BuildLevel() override
    {
        Level* level = new Level();

        // Initialize level construction
        initConstruct(level);
        
        // Set level type
        level->levelType = Level::LevelType::InitVelY;
        
        // Set hints
        std::vector<std::string> hints = {"do this", "try that", "how bout this"};
        level->hints = hints;

        // Solve for solution
        float dx = level->targetPosition.x - level->tankPosition.x;
        float t = dx/(level->initVelocity.x);
        float dy = level->targetPosition.y - level->tankPosition.y;
        float vy = (dy - (0.5f * level->gravity * t * t)) / t;  // solve for velY
        
        level->initVelocity.y = vy;
        level->solution = "The answer is " + std::to_string(vy);
        
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