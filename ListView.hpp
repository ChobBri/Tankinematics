#include "raylib.h"
#include "Level.h"

using namespace std;

struct replayButton {
    Rectangle button;
    int index = 0;
};

class ListView{
    public:
        ListView(float, float, float, float, int, vector<Level>&);
        void DrawListView();
        int isClicked();
        Level getClicked();
    private:
        replayButton drawHistoryEntry(Level, int);
        vector<replayButton> replayButtonList;
        Rectangle bounds;
        int maxEntriesShown;
        vector<Level>* allEntries;
        Level clicked;
};