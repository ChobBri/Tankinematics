//
// Created by Roy on 2022-10-30.
//

#ifndef LEVELHISTORY_LVLHISTORY_H
#define LEVELHISTORY_LVLHISTORY_H

#include <iostream>
#include <vector>
#include <string>

using namespace std;

class level{
    int lvlNum;
public:
    bool isEqual(level lvl1);
    level();
    level(int lvlNum);
    int getLvlNum();
};

class levelHistory{
    vector<level> allLevels;

public:
    vector<level> getAllLevels();
    void addLevel(level lvl);
    void moveToTop(level lvl, int position);
};
#endif //LEVELHISTORY_LVLHISTORY_H
