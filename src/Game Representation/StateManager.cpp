//
// Created by Qami on 11/23/2023.
//

#include "StateManager.h"

namespace Game {


    StateManager::StateManager() {
        auto* start = new MenuState();
        stateManager.emplace(start);
    }

    void StateManager::pop() {

    }

    void StateManager::push() {

    }

    State* StateManager::top() {
        return stateManager.top();
    }
} // Game