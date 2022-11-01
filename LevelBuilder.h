#ifndef LEVELBUILDER_H
#define LEVELBUILDER_H

#include "Level.h"

/**
 * LevelBuilder is an abstract class to represent a level builder.
*/
class LevelBuilder
{
public:
    // angleOverVel is a flag to determine whether to solve for angle or velocity
    // isGravityOn is a flag to choose whether to have gravity or not
    LevelBuilder(bool angleOverVel, bool isGravityOn)
    {
        angleOverVel_ = angleOverVel;
        isGravityOn_ = isGravityOn;
    }

    // Abstract function to build level
    virtual Level BuildLevel() = 0;

protected:
    bool angleOverVel_;  // Flag to determine whether to solve for angle or velocity
    bool isGravityOn_;  // Flag to choose whether to have gravity or not
};

#endif
