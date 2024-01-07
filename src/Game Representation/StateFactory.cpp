//
// Created by Qami on 12/27/2023.
//

#include "StateFactory.h"

#include <utility>

namespace Game {
State* StateFactory::stateFactory(const states& s, const shared_ptr<StateManager>& stateManager) {
    switch (s) {
    case MENU:
        return new MenuState(stateManager);

    case LEVEL:
        return new LevelState(stateManager);

    case PAUSED:
        return new PausedState(stateManager);

    case WON:
        return new VictoryState(stateManager);

    case LOST:
        return new GameOverState(stateManager);
    default:
        return nullptr;
    }
}

StateFactory::StateFactory(const shared_ptr<StateManager>& stateManager) : stateManager(stateManager) {}
} // namespace Game