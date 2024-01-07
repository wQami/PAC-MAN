//
// Created by Qami on 11/23/2023.
//

#include "State.h"

namespace Game {

State::State(const shared_ptr<StateManager> stateManager) : stateManager(stateManager) {}

shared_ptr<StateManager> State::getStateManager() const { return stateManager; }
} // namespace Game