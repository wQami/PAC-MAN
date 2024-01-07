//
// Created by Qami on 12/27/2023.
//

#ifndef PAC_MAN_STATEFACTORY_H
#define PAC_MAN_STATEFACTORY_H

#include "States/GameOverState.h"
#include "States/LevelState.h"
#include "States/MenuState.h"
#include "States/PausedState.h"
#include "States/VictoryState.h"

namespace Game {

class StateFactory {
private:
    shared_ptr<StateManager> stateManager;

public:
    explicit StateFactory(const shared_ptr<StateManager>& stateManager);

    static State* stateFactory(const states& s, const shared_ptr<StateManager>& stateManager);
};

} // namespace Game

#endif // PAC_MAN_STATEFACTORY_H
