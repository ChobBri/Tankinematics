#include "ListView.hpp"
#include <iostream>

using namespace std;

/**
 * Used to resolve level type to printable string 
*/
const char* levelTypeToString(Level::LevelType levelType) {
    switch (levelType)
        {
        case 0:
            return "Gravity";
            break;
        case 1:
            return "Angle";
            break;
        case 2:
            return "InitSpeed";
            break;
        case 3:
            return "InitVelX";
            break;
        default:
            return "InitVelY";
            break;
        }
}
/**
 * Creates a listView object. 
 * IMPORTANT: pass the address of levelHistory's allLevels vector.
 * That way, any changes to levelHistory are reflected in listView.
*/
ListView::ListView(float x, float y, float width, float height, int maxEntries, vector<Level>& allLevels){
    bounds = Rectangle{x, y, width, height};
    maxEntriesShown = maxEntries;
    allEntries = &allLevels;
}
    
/**
 * Draw boundary box, specified number of entries and their replay buttons.
 * Populates replayButtonList.
*/
void ListView::DrawListView(){
    DrawRectangleRec(bounds, DARKGRAY);

    int position = 0;
    replayButtonList.clear();
    replayButton temp;

    for (Level i : *(allEntries)){ //This both draws the first 10 history entries AND stores the position of their replay buttons 
        temp = drawHistoryEntry(i, position);
        replayButtonList.push_back(temp);
        position++;
        if (position >= maxEntriesShown) break;
    }

    if (allEntries->empty())
        DrawText(TextFormat("No Levels in History!"), bounds.x + 10, bounds.y + +10, 20, BLACK);
    
}

/**
 * Draws a history entry for given level in specified postion. 
 * 
 * Returns a replayButton struct which represents the position of
 * a replay button and its index in allLevels vector.
*/
replayButton ListView::drawHistoryEntry(Level level, int position){
    //for readability
    int leftBoxEdge = 244;
    int topBoxEdge = (32 + position * 48);
    int boxWidth = 472;
    int boxHeight = 44;
    int fontSize = 4;

    //Draw rectangle
    DrawRectangle(leftBoxEdge, topBoxEdge, boxWidth, boxHeight, LIGHTGRAY);

    //Draw level stats
    DrawText(TextFormat("Total Attempts: %d", level.totalAttempts),             leftBoxEdge+4, topBoxEdge+4 + 0,    fontSize, BLACK);
    DrawText(TextFormat("Successful Attempts: %d", level.successfulAttempts),   leftBoxEdge+4, topBoxEdge+4 + 10,   fontSize, BLACK);
    DrawText(TextFormat("replayButton's index value: %d", position),            leftBoxEdge+4, topBoxEdge+4 + 20,   fontSize, BLACK);
    DrawText(levelTypeToString(level.levelType),                                leftBoxEdge+4, topBoxEdge+4 + 30,   fontSize, BLACK);

    //Draw play button and text
    Rectangle playButton = {leftBoxEdge + boxWidth - 94, topBoxEdge + 4, 90, boxHeight-8};
    DrawRectangleRec(playButton, LIME);
    DrawText(TextFormat("Replay"), leftBoxEdge + boxWidth - 90, topBoxEdge + 8, 26, WHITE);

    replayButton returnValue{replayButton{playButton, position}};

    return returnValue;
}

/**
 * Returns index of level which was selected to be replayed
 * IF none, returns -1
*/
int ListView::isClicked(){
    for (replayButton i : replayButtonList){
        if (CheckCollisionPointRec(GetMousePosition(), i.button) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
            clicked = &((*allEntries)[0]); //this is just the address of allLevels[0], doesnt matter what's in that position
            return i.index; 
        }
    }
    return -1;
}

/**
 * Returns the level corresponding to the replay button which was clicked.
*/
Level* ListView::getClicked(){
    return &((*allEntries)[0]); //Could instead just return address of allLevels[0]
}