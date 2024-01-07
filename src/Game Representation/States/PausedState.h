//
// Created by Qami on 11/28/2023.
//

#ifndef PAC_MAN_PAUSEDSTATE_H
#define PAC_MAN_PAUSEDSTATE_H

#include "../State.h"
#include "../StateManager.h"

namespace Game {

class PausedState : public State {
private:
    bool drawnOnce;

public:
    explicit PausedState(const shared_ptr<StateManager>& context);
    void draw(RenderWindow& window) override;
    void keyPress() override;

    void handlePeriod() override;
};

} // namespace Game

#endif // PAC_MAN_PAUSEDSTATE_H
