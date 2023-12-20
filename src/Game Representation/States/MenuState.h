//
// Created by Qami on 11/28/2023.
//

#ifndef PAC_MAN_MENUSTATE_H
#define PAC_MAN_MENUSTATE_H

#include <set>
#include "../State.h"

namespace Game {

    class MenuState : public State {
    private:
    public:
        MenuState();
        ~MenuState() override = default;
    };

} // Game

#endif //PAC_MAN_MENUSTATE_H
