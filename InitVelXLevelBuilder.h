#ifndef INITVELXLEVELBUILDER_H
#define INITVELXLEVELBUILDER_H

#include "LevelBuilder.h"
#include "LevelConstraints.h"
#include "Level.h"
#include <random>
#include <vector>
#include <string>

/**
 * InitVelXLevelBuilder is an abstract class to represent a level builder for initVelX levels.
*/
class InitVelXLevelBuilder : public LevelBuilder
{
public:
    Level* BuildLevel() override
    {
        Level* level = new Level();

        // Initialize level construction
        initConstruct(level);


        // Set level type
        level->levelType = Level::LevelType::InitVelX;
        
        // Set hints
        std::vector<std::string> hints = {"do this", "try that", "how bout this"};
        level->hints = hints;

        // Solve for solution
        bool legalLevel = false;
        do {
            // delta values
            float dx = level->targetPosition.x - level->tankPosition.x;
            float dy = level->targetPosition.y - level->tankPosition.y;

            // quadratic formula values
            float a = 0.5f * level->gravity;
            float b = level->initVelocity.y;
            float c = -dy;
            float radicand = (b * b) - (4 * a * c);

            // if level is impossible, rebuild
            if (radicand < 0.0f)
            {
                initConstruct(level);
                continue;
            }

            // solve using quadratic formula
            float t1 = (-b + sqrtf(radicand)) / (2.0f * a);
            float t2 = (-b - sqrtf(radicand)) / (2.0f * a);

            float t = 0.0f;

            // get valid value
            if (t1 < 0.0f)
            {
                t = t2;
            }
            else if (t2 < 0.0f)
            {
                t = t1;
            }
            else
            {
                t = fmaxf(t1, t2);
            }

            // solve for velX
            float vx = dx / t;
            
            level->initVelocity.x = vx;
            level->solution = vx;

            level->angleOverVel = false;
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