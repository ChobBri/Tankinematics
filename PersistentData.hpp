#ifndef PERSISTENTDATA_HPP
#define PERSISTENTDATA_HPP

#include "Level.h"
#include <fstream>

using namespace std;

class PersistentData {
    public:
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

        /**
         * Will return isError flag
        */
        static bool isError();

        /**
         * Used to initialize fields in place of constructor because theyre static
        */
        static void initialize(string, bool);

    private:
        /**
         * This is the relative path to the file that levels will 
         * be read from / written to.
        */
        static string relativeLevelFilePath;

        /**
         * This flag is set when loading to indicate an error occured.
        */
        static bool wasError;
};

#endif