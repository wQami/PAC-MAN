//
// Created by Qami on 11/23/2023.
//

#ifndef PAC_MAN_STATE_H
#define PAC_MAN_STATE_H

#include "../Logic Library/Score.h"
#include "../globalGame.h"
#include "SFML/Graphics.hpp"
#include <iostream>
#include <memory>
#include <stack>
#include <string>

using namespace std;
using namespace sf;

namespace Game {
class StateManager;
class State {
    shared_ptr<StateManager> stateManager;

public:
    State() = default;
    ~State() = default;
    explicit State(const shared_ptr<StateManager> stateManager);
    virtual void draw(RenderWindow& window) = 0;
    virtual void keyPress() = 0;
    virtual void handlePeriod() = 0;
    [[nodiscard]] shared_ptr<StateManager> getStateManager() const;
};
} // namespace Game

#endif // PAC_MAN_STATE_H
