#include "PersistentData.hpp"
#include <sstream>
#include <iostream>

using namespace std;

string PersistentData::relativeLevelFilePath = "levelData/level.dat";

void PersistentData::saveLevels(vector<Level> source){
    ofstream outputStream(PersistentData::relativeLevelFilePath, ios::out);
    for (Level i : source){
        outputStream << i.gravity << '\t' << i.angle << '\t' << i.initVelocity.x << '\t' << i.initVelocity.y << '\t' << i.tankPosition.x << '\t' << i.tankPosition.y << '\t' << i.targetPosition.x << '\t' << i.targetPosition.y << '\t' << i.angleOverVel << '\n';
        
        outputStream << i.solution << '\n';
        
        outputStream << to_string(i.hints.size()) << '\n';

        for (string h : i.hints){
        outputStream << h << '\t';
        } 

        outputStream << '\n';
    }       
    
    outputStream.close();
    return;
}

//maybe should take a pointer to vector<Level> or use heap instead of copy on stack?
vector<Level> PersistentData::loadLevels(){
    ifstream inputStream(relativeLevelFilePath);
    string line = "";
    vector<Level> importedLevels;

    string hintCount = "";

    float gravity = 0.0f;
    float angle = 0.0f;
    Vector2 initVelocity = {0.0f, 0.0f};
    Vector2 tankPosition = {0.0f, 0.0f};
    Vector2 targetPosition = {0.0f, 0.0f};
    std::vector<std::string> hints;
    std::string solution;
    bool angleOverVel = true;

    while (std::getline(inputStream, line)){
        
        //Extract all variables which don't (can't) contain spaces
        std::istringstream issLine(line);
        issLine >> gravity >> angle >> initVelocity.x >> initVelocity.y >> tankPosition.x >> tankPosition.y >> targetPosition.x >> targetPosition.y >> angleOverVel;
        
        //Second line is "solution" string
        std::getline(inputStream, line);
        solution = line;

        //Push level with all EXCEPT hints populated
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

        //Read the number of hints, then read that many lines (as hints)
        std::getline(inputStream, hintCount);
        for (int i = 0; i < stoi(hintCount); i++){
            std::getline(inputStream, line);
            importedLevels.back().hints.push_back(line);  
        }
        
    }
    return importedLevels;
}

void PersistentData::debugLevel(){

    //debug
    struct Level test1 {
        9.8, //gravity
        45.0, //angle
        {10, 4}, //init velocity
        {6, 9}, //tank position
        {9, 6}, //target position
        {{"hint_sample_1"}}, //hints
        "just solve it dummy1", //solution
        true //angle override flag
    };

    struct Level test2 {
        19.8, //gravity
        145.0, //angle
        {110, 14}, //init velocity
        {61, 91}, //tank position
        {91, 61}, //target position
        {{"hint_sample_2"},{"hint_sample_22"}}, //hints
        "just solve it dummy2", //solution
        false //angle override flag
    };

    vector<Level> levelList {test1};
    levelList.push_back(test2);

    PersistentData::saveLevels(levelList);

    vector<Level> loadedLevels = PersistentData::loadLevels();

    for (Level i : loadedLevels){
        cout << "graivty: " << i.gravity << "\nangle: " << i.angle << "\ninitVelocity: (" << i.initVelocity.x << ", " << i.initVelocity.y << ")\ntankPosition: (" << i.tankPosition.x << ", " << i.tankPosition.y << ")\ntargetPosition: (" << i.targetPosition.x << ", " << i.targetPosition.y << ")\nhints: ";
        for (string i : i.hints){
            cout << i << " ";
        }
        cout << "\nsolution: " << i.solution << "\nangleOverVel: ";
        if (i.angleOverVel){
            cout << "true\n\n";
        } else {
            cout << "false\n\n";
        }
    }

}