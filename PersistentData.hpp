#include "Level.h"
#include <fstream>

using namespace std;

class PersistentData {
    public:
        static string relativeLevelFilePath;

        static void saveLevels(vector<Level>);

        static vector<Level> loadLevels();

        static void debugLevel();
};