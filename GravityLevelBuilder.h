#ifndef GRAVITYLEVELBUILDER_H
#define GRAVITYLEVELBUILDER_H

#include "LevelBuilder.h"
#include "Level.h"
#include <random>
#include <vector>
#include <string>

class GravityLevelBuilder : public LevelBuilder
{
public:
    GravityLevelBuilder(bool angleOverVel)
    : LevelBuilder(angleOverVel, true)
    {}

    Level BuildLevel() override
    {
        std::random_device rd;
        std::mt19937 rng(rd());
        
        Level level;

        std::uniform_real_distribution<float> gravityDist(1.0f, 10.0f);
        level.gravity = gravityDist(rng);

        level.angleOverVel = angleOverVel_;

        std::uniform_real_distribution<float> angleDist(0.0f, 90.0f);
        level.angle = angleDist(rng);

        std::uniform_real_distribution<float> velXDist(1.0f, 10.0f);
        float velx = velXDist(rng);
        std::uniform_real_distribution<float> velYDist(1.0f, 10.0f);
        float vely = velYDist(rng);

        Vector2 initVel = {velx, vely};
        level.initVelocity = initVel;

        std::vector<std::string> hints = {"do this", "try that", "how bout this"};
        level.hints = hints;

        level.solution = "The answer is \"34.2\"";
        return level;
    }
};

#endif

// Example of when mixed with polymorphism
/**
 * 
 *  std::vector<LevelBuilder*> v;

    for (size_t i = 0; i < 3; i++)
    {
        GravityLevelBuilder builder(true);
        v.push_back(&builder);
    }

    for (size_t i = 0; i < v.size(); i++)
    {
        Level l = v[i]->BuildLevel();
        std::cout << l.angle << " " << l.gravity << l.hints[0] << l.hints[1] << l.hints[2] << std::endl;
    }
 * 
*/