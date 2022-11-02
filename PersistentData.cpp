#include "PersistentData.hpp"
#include <sstream>
#include <iostream>

using namespace std;

string PersistentData::relativeLevelFilePath = "levelData/level.dat";

void PersistentData::saveLevels(vector<Level> source){
    ofstream outputStream(PersistentData::relativeLevelFilePath, ios::out);
    for (Level i : source){
        //Write fields which can't contain any spaces
        outputStream << i.gravity << '\t' << i.angle << '\t' << i.initSpeed <<'\t' << i.initVelocity.x << '\t' << i.initVelocity.y << '\t' << i.tankPosition.x << '\t' << i.tankPosition.y << '\t' << i.targetPosition.x << '\t' << i.targetPosition.y << '\t' << i.angleOverVel << '\t' << i.totalAttempts << '\t' << i.successfulAttempts << '\t' << i.time << '\t' << i.levelType << '\n';
        
        //Write solution (which can contain spaces)
        outputStream << i.solution << '\n';
        
        //Write number of hints
        outputStream << to_string(i.hints.size()) << '\n';

        //Write all hints
        for (string h : i.hints){
        outputStream << h << '\t';
        } 

        outputStream << '\n';
    }       
    
    outputStream.close();
    return;
}

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
    std::string solution;
    bool angleOverVel = true;
    int totalAttempts = 0;
    int successfulAttempts = 0;
    float time = 0.0f; // in seconds
    Level::LevelType levelType;
    string levelTypeString = "";

    while (std::getline(inputStream, line)){
        
        //Extract all variables which don't (can't) contain spaces
        std::istringstream issLine(line);
        issLine >> gravity >> angle >> initSpeed >> initVelocity.x >> initVelocity.y >> tankPosition.x >> tankPosition.y >> targetPosition.x >> targetPosition.y >> angleOverVel >> totalAttempts >> successfulAttempts >> time >> levelTypeString;
        
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

        //Second line is "solution" string
        std::getline(inputStream, line);
        solution = line;

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

void PersistentData::debugLevel(){
    
    //Create two levels
    struct Level test1 {
        9.8, //gravity
        45.0, //angle
        6969.69, //speed
        {10, 4}, //init velocity
        {6, 9}, //tank position
        {9, 6}, //target position
        {{"hint_sample_1"}}, //hints
        "just solve it dummy1", //solution
        true, //angle override flag
        12, //total attempts
        1, //successful attempts
        420.0, //time
        Level::LevelType::Angle //level type
    };

    struct Level test2 {
        19.8, //gravity
        145.0, //angle
        420.69, //speed
        {110, 14}, //init velocity
        {61, 91}, //tank position
        {91, 61}, //target position
        {{"hint_sample_2"},{"hint_sample_22"}}, //hints
        "just solve it dummy2", //solution
        false, //angle override flag
        2, //total attempts
        0, //successful attempts
        68.0, //time
        Level::LevelType::Gravity //level type
    };

    //Create vector<Level> to be written to disk
    vector<Level> levelList {test1};
    levelList.push_back(test2);
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
            cout << "true";
        } else {
            cout << "false";
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