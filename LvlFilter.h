#ifndef LVLFILTER_H
#define LVLFILTER_H

// Array to store settings to generate specific levels
class LvlFilter{
public:        
        LvlFilter();
        LvlFilter(bool, bool, bool, bool, bool);
        void updateArray(bool isGrav, bool isAngle, bool isVelX, bool isVelY, bool isSpeed);
        void toggleIndex(int);
        bool* getFilters();
private:
        bool filters[5];
};

#endif