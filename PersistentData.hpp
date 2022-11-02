#include "Level.h"
#include <fstream>

using namespace std;

class PersistentData {
    public:
        /**
         * This is the relative path to the file that levels will 
         * be read from / written to.
        */
        static string relativeLevelFilePath;

        /**
         * Invoked before exiting program to save persistent data 
         * (level history) to disk.
        */
        static void saveLevels(vector<Level>);

        /**
         * Invoked during initialization to populate levelHistory.
        */
        static vector<Level> loadLevels();

        /**
         * Will create two levels, save them to disk, load them 
         * back from disk then print their contents to terminal.
        */
        static void debugLevel();
};