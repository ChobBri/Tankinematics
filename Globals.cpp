#include "Globals.hpp"

using namespace std;

gameStates Globals::currentState{TITLE};
int Globals::otherGlobalVariable{69};

void Globals::setCurrentState(gameStates newState){
    currentState = newState;
    return;
}