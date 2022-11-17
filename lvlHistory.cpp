//
// Created by Roy on 2022-10-30.
//

#include "lvlHistory.h"
#define MAX_SIZE 10

using namespace std;

vector<Level> levelHistory::getAllLevels() {
    return allLevels;
}

void levelHistory::addLevel(Level lvl) {
    allLevels.insert(allLevels.begin(), lvl);
    if (allLevels.size() > MAX_SIZE)
        allLevels.resize(MAX_SIZE);
    return;
}

void levelHistory::moveToTop(int position){
    allLevels.insert(allLevels.begin(), allLevels[position]);
    allLevels.erase(allLevels.begin() + position + 1);
    return;
}

