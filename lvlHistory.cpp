//
// Created by Roy on 2022-10-30.
//

#include "lvlHistory.h"
#define MAX_SIZE 10

using namespace std;

bool level::isEqual(level lvl) {
    return (this->lvlNum == lvl.lvlNum);
}

int level::getLvlNum() {
    return this->lvlNum;
}

level::level(int number){
    lvlNum = number;
}

level::level(){
    lvlNum = -1;
}

vector<level> levelHistory::getAllLevels() {
    return allLevels;
}

void levelHistory::addLevel(level lvl) {
    int flag = 0;
    for (int i = 0; i < allLevels.size(); i++){
        if (lvl.isEqual(allLevels[i])){
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

void levelHistory::moveToTop(level lvl, int position){
    allLevels.insert(allLevels.begin(), lvl);
    allLevels.erase(allLevels.begin()+position+1);
    return;
}

