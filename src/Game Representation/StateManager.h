//
// Created by Qami on 11/23/2023.
//

#ifndef PAC_MAN_STATEMANAGER_H
#define PAC_MAN_STATEMANAGER_H
#include <stack>

#include "State.h"
#include "States/MenuState.h"

using namespace std;

namespace Game {
    class StateManager {
    private:
        stack<State*> stateManager;
    public:
        StateManager();
        void pop();
        void push();
        State* top();
    };

} // Game

#endif //PAC_MAN_STATEMANAGER_H
