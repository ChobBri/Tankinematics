#include "PersistentData.hpp"
#include <sstream>
#include <iostream>

using namespace std;

string PersistentData::relativeLevelFilePath = "levelData/level.dat";

void PersistentData::saveLevel(vector<Level> source){
    ofstream outputStream(PersistentData::relativeLevelFilePath, ios::out);
    for (Level i : source){
        outputStream << i.gravity << '\t' << i.angle << '\t' << i.initVelocity.x << '\t' << i.initVelocity.y << '\t' << i.tankPosition.x << '\t' << i.tankPosition.y << '\t' << i.targetPosition.x << '\t' << i.targetPosition.y << '\t' << i.solution << '\t' << i.angleOverVel << '\n';
        
        for (string h : i.hints){
        outputStream << h << '\t';
        } 

        outputStream << '\n';
    }       
    
    outputStream.close();
    return;
}

//maybe should take a pointer to vector<Level> or use heap instead of copy on stack?
vector<Level> PersistentData::readLevel(){
    ifstream inputStream(relativeLevelFilePath);
    string line = "";
    vector<Level> importedLevels;

    float gravity = 0.0f;
    float angle = 0.0f;
    Vector2 initVelocity = {0.0f, 0.0f};
    Vector2 tankPosition = {0.0f, 0.0f};
    Vector2 targetPosition = {0.0f, 0.0f};
    std::vector<std::string> hints;
    std::string solution;
    bool angleOverVel = true;

    while (std::getline(inputStream, line)){
        
        std::istringstream issLine(line);
        issLine >> gravity >> angle >> initVelocity.x >> initVelocity.y >> tankPosition.x >> tankPosition.y >> targetPosition.x >> targetPosition.y >> solution >> angleOverVel;
        cout << solution; // DOESNT LOAD WHOLE SOLUTION, ONLY FIRST WORD BEFORE SPACE
        importedLevels.emplace_back(Level{
            gravity,
            angle,
            {initVelocity.x, initVelocity.y},
            {tankPosition.x, tankPosition.y},
            {targetPosition.x, targetPosition.y},
            {},
            solution,
            angleOverVel
        });

        std::getline(inputStream, line);
        importedLevels.back().hints.push_back("s");
    }
    return importedLevels;
}