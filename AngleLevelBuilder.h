#ifndef ANGLELEVELBUILDER_H
#define ANGLELEVELBUILDER_H

#include "LevelBuilder.h"
#include "LevelConstraints.h"
#include "Level.h"
#include <random>
#include <vector>
#include <string>

/**
 * AngleLevelBuilder is an abstract class to represent a level builder for angle levels.
*/
class AngleLevelBuilder : public LevelBuilder
{
public:
    Level* BuildLevel() override
    {
        Level* level = new Level();

        // Initialize level construction
        initConstruct(level);

        // Set level type
        level->levelType = Level::LevelType::Angle;
        
        // Set hints
        std::vector<std::string> hints = {"do this", "try that", "how bout this"};
        level->hints = hints;

        bool legalLevel = false;

        // Solve for solution
        do {
            // delta values
            float dx = level->targetPosition.x - level->tankPosition.x;
            float dy = level->targetPosition.y - level->tankPosition.y;

            // values for quadratic formula
            float a = level->gravity * dx * dx;
            float b = 2 * level->initSpeed * level->initSpeed * dx;
            float c = level->gravity * dx * dx - 2 * level->initSpeed * level->initSpeed * dy;
            float radicand = (b * b) - (4 * a * c);

            // If level is impossible to solve, rebuild
            if (radicand < 0.0f)
            {
                initConstruct(level);
                continue;
            }

            // Solve tan using quadratic formula
            float tan1 = (-b + sqrtf(radicand)) / (2.0f * a);
            float tan2 = (-b - sqrtf(radicand)) / (2.0f * a);

            float tan = 0.0f;

            // Choose valid value
            if (tan1 < 0.0f)
            {
                tan = tan2;
            }
            else if (tan2 < 0.0f)
            {
                tan = tan1;
            }
            else
            {
                tan = fminf(tan1, tan2);
            }

            // Find angle
            float angle = atanf(tan) * RAD2DEG;

            level->angle = angle;
            level->solution = "The answer is " + std::to_string(angle);
            level->angleOverVel = true;
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