//
// Created by Qami on 11/20/2023.
//

#ifndef PAC_MAN_GAME_H
#define PAC_MAN_GAME_H

#include "../Logic Library/Stopwatch.h"
#include "../Logic Library/World.h"
#include "SFML/Graphics.hpp"
#include "StateManager.h"
#include <string>

using namespace std;
using namespace sf;

namespace Game {
class Game {
private:
    RenderWindow window;
    shared_ptr<StateManager> stateManager;

public:
    void run();
    void handleStackChange(int&);
    void drawLevel();
    Game();
};
}; // namespace Game

#endif // PAC_MAN_GAME_H
