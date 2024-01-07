//
// Created by Qami on 11/28/2023.
//

#ifndef PAC_MAN_VICTORYSTATE_H
#define PAC_MAN_VICTORYSTATE_H

#include "../State.h"
#include "../StateManager.h"

namespace Game {

class VictoryState : public State {
private:
public:
    explicit VictoryState(const shared_ptr<StateManager>& context);
    void draw(RenderWindow& window) override;
    void keyPress() override;

    void handlePeriod() override;
};
} // namespace Game

#endif // PAC_MAN_VICTORYSTATE_H
