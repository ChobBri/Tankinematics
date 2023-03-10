#ifndef SIM_H
#define SIM_H

#include <iostream>
#include <string>
#include "raylib.h"
#include "Level.h"
#include "lvlHistory.h"
#include "LvlFilter.h"
#include <string>


class Simulation{
    private:
    
    Level* level;
    
    float gravity;
    float angle;
    float speed;
    float initVelX;
    float initVelY;

    float acTime;
    Rectangle proj;
    Vector2 initPos;
    Vector2 targetPos;
 

    Rectangle infoBox;
    Vector2 tankPos;
    Rectangle field; 
    

    bool isSimulating = false;//

    Texture2D genericBackground;
    Texture2D tankSprite;
    Texture2D castleSprite;
    
    public:
    Simulation(Texture2D& genericBkg_, Texture2D& tankSprite_, Texture2D& castleSprite_);
    //getting position
    Vector2 getPosition(float t);
    //checking if it hit the target
    bool targetConfirm();
    //checking if it hit the ground
    bool failConfirm();
 
    Rectangle getProj();
    
    Vector2 getTargetPos();
    std::string getSolutionString();


    void initSimulation(levelHistory&, LvlFilter&);
    void initSimulation(Level* lvl);
    void update();
    void display();

    void playSimulation();
    void resetSimulation();

    bool simulating();

};

#endif