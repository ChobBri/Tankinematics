#ifndef SPEEDLEVELBUILDER_H
#define SPEEDLEVELBUILDER_H

#include "LevelBuilder.h"
#include "LevelConstraints.h"
#include "Level.h"
#include <random>
#include <vector>
#include <string>

/**
 * SpeedLevelBuilder is an abstract class to represent a level builder for gravity levels.
*/
class SpeedLevelBuilder : public LevelBuilder
{
public:
    Level* BuildLevel() override
    {
        Level* level = new Level();

        // Initialize level construction
        initConstruct(level);

        // Set level type
        level->levelType = Level::LevelType::InitSpeed;
        
        // Set hints
        std::vector<std::string> hints = {"do this", "try that", "how bout this"};
        level->hints = hints;

        // Solve for solution
        bool legalLevel = false;
        do {
            // delta values
            float dx = level->targetPosition.x - level->tankPosition.x;
            float dy = level->targetPosition.y - level->tankPosition.y;

            // solve for speed^2
            float speedsqrd = (level->gravity * dx * dx) / (2 * (dy - tanf(level->angle * DEG2RAD) * dx) * cosf(level->angle * DEG2RAD) * cosf(level->angle * DEG2RAD));
            
            // If level is impossible, rebuild
            if (speedsqrd < 0.0f)
            {
                initConstruct(level);
                continue;
            }
                
            // get actual speed
            float speed = sqrtf(speedsqrd);
            level->initSpeed = speed;
            level->solution = "The answer is " + std::to_string(speed);
            legalLevel = true;
        } while (!legalLevel);
        
        
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