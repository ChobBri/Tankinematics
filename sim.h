#include <iostream>
#include <string>
#include "raylib.h"

class simulation{
    private:
    int screenWidth;
    int screenHeight;
    float grav;
    float angle;
    float initVel;
    float acTime;
    Rectangle proj;
    Vector2 initPos;
    
    public:
    simulation(int width, int height, float gravi, float ang, float initvel, Vector2 init);

    //getting position
    Vector2 getPosition(Vector2 posOfProj);
    //checking if it hit the target
    bool targetConfirm(int lineY, Vector2 targetLoc);
    //checking if it hit the ground
    bool failConfirm(int lineY);
    //the projectile --> maybe better animation? idk
    Rectangle getProj();

};