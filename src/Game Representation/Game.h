//
// Created by Qami on 11/20/2023.
//

#ifndef PAC_MAN_GAME_H
#define PAC_MAN_GAME_H

#include <string>
#include "SFML/Graphics.hpp"
#include "StateManager.h"
#include "../Logic Library/World.h"

using namespace std;
using namespace sf;

namespace Game {
    class Game {
    private:
        RenderWindow window;
        StateManager stateManager;
        Logic::World* world;

    public:
        void run();
    };
};

#endif //PAC_MAN_GAME_H
