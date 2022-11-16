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
    int flag = 0;
    for (int i = 0; i < allLevels.size(); i++){
        if (isEqual(lvl, allLevels[i])){
            moveToTop(lvl, i);
            flag = 1;
            break;
        }
    }
    if (flag == 0) {
        allLevels.insert(allLevels.begin(), lvl);
    }
    if (allLevels.size() > MAX_SIZE){
        allLevels.resize(MAX_SIZE);
    }
    return;
}

void levelHistory::moveToTop(Level lvl, int position){
    allLevels.insert(allLevels.begin(), lvl);
    allLevels.erase(allLevels.begin()+position+1);
    return;
}

