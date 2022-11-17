#include "PersistentData.hpp"
#include <sstream>
#include <iostream>

using namespace std;

string PersistentData::relativeLevelFilePath = "levelData/level.dat";

/**
 * Save the passed vector of levels to disk.
*/
void PersistentData::saveLevels(vector<Level> source){
    ofstream outputStream(PersistentData::relativeLevelFilePath, ios::out);
    for (Level i : source){
        //Write fields which can't contain any spaces
        outputStream << i.gravity << '\t' << i.angle << '\t' << i.initSpeed <<'\t' << i.initVelocity.x << '\t' << i.initVelocity.y << '\t' << i.tankPosition.x << '\t' << i.tankPosition.y << '\t' << i.targetPosition.x << '\t' << i.targetPosition.y << '\t' << i.angleOverVel << '\t' << i.totalAttempts << '\t' << i.successfulAttempts << '\t' << i.time << '\t' << i.levelType << '\t' << i.solution << '\n';
        
        //Write number of hints
        outputStream << to_string(i.hints.size());

        //Write all hints
        for (string h : i.hints){
        outputStream << "\n" << h;
        } 

        outputStream << '\n';
    }       
    
    outputStream.close();
    return;
}

/**
 *Loads level history data from file on disk, then returns 
 a vector of levels from extracted data. 
*/
vector<Level> PersistentData::loadLevels(){
    //Used in loading contents of file
    ifstream inputStream(relativeLevelFilePath);
    string line = "";
    vector<Level> importedLevels;
    string hintCount = "";

    //Temporary holders for loaded fields
    float gravity = 0.0f;
    float angle = 0.0f;
    float initSpeed = 0.0f;
    Vector2 initVelocity = {0.0f, 0.0f};
    Vector2 tankPosition = {0.0f, 0.0f};
    Vector2 targetPosition = {0.0f, 0.0f};
    std::vector<std::string> hints;
    float solution;
    bool angleOverVel = true;
    int totalAttempts = 0;
    int successfulAttempts = 0;
    float time = 0.0f; // in seconds
    Level::LevelType levelType;
    string levelTypeString = "";

    while (std::getline(inputStream, line)){
        
        //Extract all variables which don't (can't) contain spaces
        std::istringstream issLine(line);
        issLine >> gravity >> angle >> initSpeed >> initVelocity.x >> initVelocity.y >> tankPosition.x >> tankPosition.y >> targetPosition.x >> targetPosition.y >> angleOverVel >> totalAttempts >> successfulAttempts >> time >> levelTypeString >> solution;
        
        //convert (string)levelType to levelType 
        switch (stoi(levelTypeString))
        {
        case 0:
            levelType = Level::LevelType::Gravity;
            break;
        case 1:
            levelType = Level::LevelType::Angle;
            break;
        case 2:
            levelType = Level::LevelType::InitSpeed;
            break;
        case 3:
            levelType = Level::LevelType::InitVelX;
            break;
        default:
            levelType = Level::LevelType::InitVelY;
            break;
        }

        //Push level with all EXCEPT hints populated
        importedLevels.emplace_back(Level{
            gravity,
            angle,
            initSpeed,
            {initVelocity.x, initVelocity.y},
            {tankPosition.x, tankPosition.y},
            {targetPosition.x, targetPosition.y},
            {}, //Hints is left blank for now
            solution,
            angleOverVel,
            totalAttempts,
            successfulAttempts,
            time,
            levelType
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


/**
 * ---DEBUG---
 * Creates and saves 10 sample levels, then loads them from 
 * file and displays their contents in terminal. 
*/
void PersistentData::debugLevel(){
    
    //This will eventually be "allLevels"
    vector<Level> levelList;

    //Generate 11 levels with varying information
    for (int i = 0; i < 10; i++){
        levelList.emplace_back(Level{
            1.2f*i, //gravity
            15.0f*i, //angle
            9.2f*i, //speed
            {1.0f*i, 2.0f*i}, //init velocity
            {3.0f*i, 1.23f*i}, //tank position
            {1.1f*i, 6.1f*i}, //target position
            {{("SAMPLEHINT" + to_string(i))}, {"Test hint"}}, //hints
            (float)2.1*i, //solution
            true, //angle override flag
            i, //total attempts
            i*4, //successful attempts
            42.0f*i, //time
            (i%2) ? Level::LevelType::Gravity : Level::LevelType::Angle //level type 
        });
    }
    PersistentData::saveLevels(levelList);

    //Load levels back into new vector<Level> from disk
    vector<Level> loadedLevels = PersistentData::loadLevels();

    //Print formatted contents of loaded levels
    for (Level i : loadedLevels){
        cout << "graivty: " << i.gravity << "\nangle: " << i.angle << "\ninitSpeed: " << i.initSpeed << "\ninitVelocity: (" << i.initVelocity.x << ", " << i.initVelocity.y << ")\ntankPosition: (" << i.tankPosition.x << ", " << i.tankPosition.y << ")\ntargetPosition: (" << i.targetPosition.x << ", " << i.targetPosition.y << ")\nhints: ";
        for (string i : i.hints){
            cout << i << " ";
        }
        cout << "\nsolution: " << i.solution << "\nangleOverVel: ";
        if (i.angleOverVel){
            cout << "true\n";
        } else {
            cout << "false\n";
        }

        for (string hint : i.hints){
            cout << "A hint: " << hint << '\n';
        }

        cout << "\ntotalAttempts: " << i.totalAttempts << "\nsuccessfulAttempts: " << i.successfulAttempts << "\ntime: " << i.time << "\nlevelType: ";

        switch (i.levelType)
        {
        case 0:
            cout << "Gravity\n\n";
            break;
        case 1:
            cout << "Angle\n\n";
            break;
        case 2:
            cout << "InitSpeed\n\n";
            break;
        case 3:
            cout << "InitVelX\n\n";
            break;
        default:
            cout << "InitVelY\n\n";
            break;
        }

    } 

}