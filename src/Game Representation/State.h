//
// Created by Qami on 11/23/2023.
//

#ifndef PAC_MAN_STATE_H
#define PAC_MAN_STATE_H

namespace Game {

    class State {

    };

    class MenuState : private State{

    };

    class LevelState : private State {

    };

    class PausedState : private State {

    };

    class VictoryState : private State {

    };

} // Game

#endif //PAC_MAN_STATE_H
