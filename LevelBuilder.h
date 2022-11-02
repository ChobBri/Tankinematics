#ifndef LEVELBUILDER_H
#define LEVELBUILDER_H

#include "Level.h"

/**
 * LevelBuilder is an abstract class to represent a level builder.
*/
class LevelBuilder
{
public:
    virtual ~LevelBuilder() = default;
    // Abstract function to build level
    virtual Level* BuildLevel() = 0;
};

#endif
