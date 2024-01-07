//
// Created by Qami on 11/28/2023.
//

#ifndef PAC_MAN_MENUSTATE_H
#define PAC_MAN_MENUSTATE_H

#pragma once
#include "../State.h"
#include <set>

namespace Game {
class MenuState : public State {
public:
    MenuState();
    explicit MenuState(const shared_ptr<StateManager>& s);
    void draw(RenderWindow& window) override;
    void keyPress() override;

    void handlePeriod() override;
};

} // namespace Game

#endif // PAC_MAN_MENUSTATE_H
