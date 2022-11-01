using namespace std;

enum gameStates {TITLE = 0, MAIN_MENU, ANGLE_LEVEL, WIND_LEVEL, SUCCESS, FAILURE, HINT, HISTORY, SIMULATION};

class Globals {
    public:
        static gameStates currentState;
        static int otherGlobalVariable;

        void static setCurrentState(gameStates);
};