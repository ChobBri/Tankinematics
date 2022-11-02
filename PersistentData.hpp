#include "Level.h"
#include <fstream>

using namespace std;

class PersistentData {
    public:
        static string relativeLevelFilePath;

        static void saveLevel(vector<Level>);

        static vector<Level> readLevel();
    private:
};