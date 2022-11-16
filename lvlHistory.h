//
// Created by Roy on 2022-10-30.
//

#ifndef LEVELHISTORY_LVLHISTORY_H
#define LEVELHISTORY_LVLHISTORY_H

#include <iostream>
#include <vector>
#include <string>
#include "Level.h"

using namespace std;


class levelHistory{
    vector<Level> allLevels;

public:
    vector<Level> getAllLevels();
    void addLevel(Level lvl);
    void moveToTop(Level lvl, int position);
};
#endif //LEVELHISTORY_LVLHISTORY_H