#include "raylib.h"
#include "Level.h"

using namespace std;

struct replayButton {
    Rectangle button;
    int index = 0;
};

class ListView{
    public:
        ListView(int, int, int, int, int, vector<Level>&);
        void DrawListView();
        bool isClicked();
        Level getClicked();
    private:
        replayButton drawHistoryEntry(Level, int);
        vector<replayButton> replayButtonList;
        Rectangle bounds;
        int maxEntriesShown;
        vector<Level>* allEntries;
        Level clicked;
};