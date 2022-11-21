#include "LvlFilter.h"

LvlFilter::LvlFilter(){
    filters[0] = false;
    filters[1] = false;
    filters[2] = false;
    filters[3] = false;
    filters[4] = false;
}
LvlFilter::LvlFilter(bool isGrav, bool isAngle, bool isVelX, bool isVelY, bool isSpeed){
    filters[0] = isGrav;
    filters[1] = isAngle;
    filters[2] = isVelX;
    filters[3] = isVelY;
    filters[4] = isSpeed;
}
void LvlFilter::updateArray(bool isGrav, bool isAngle, bool isVelX, bool isVelY, bool isSpeed){
    filters[0] = isGrav;
    filters[1] = isAngle;
    filters[2] = isVelX;
    filters[3] = isVelY;
    filters[4] = isSpeed;
}
bool* LvlFilter::getFilters(){
    return this->filters;
}
void LvlFilter::toggleIndex(int i) {
    filters[i] = !filters[i];
}
