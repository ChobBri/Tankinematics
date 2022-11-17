#ifndef LEVELCONSTRAINTS_H
#define LEVELCONSTRAINTS_H

// LevelConstraints namespace contains the constraints for building a level
namespace LevelConstraints
{
    static constexpr float MIN_ANGLE = 20.0f;
    static constexpr float MAX_ANGLE = 80.0f;
    static constexpr float MIN_SPEED = 50.0f;
    static constexpr float MAX_SPEED = 100.0f;
    static constexpr float MIN_GRAVITY = 10.0f;  // absolute value
    static constexpr float MAX_GRAVITY = 60.0f;  // absolute value
    static constexpr float MIN_INIT_VELX = 100.0f;
    static constexpr float MAX_INIT_VELX = 500.0f;
    static constexpr float MIN_INIT_VELY = 50.0f;
    static constexpr float MAX_INIT_VELY = 300.0f;
    static constexpr float MIN_DIST_X = 475.0f;
    static constexpr float MAX_DIST_X = 600.0f;
    static constexpr float MIN_DIST_Y = 20.0f;
    static constexpr float MAX_DIST_Y = 200.0f;
}

#endif