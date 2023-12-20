#include <SFML/Graphics.hpp>
#include <iostream>
#include "Game Representation/Game.h"
#include "Logic Library/Score.h"
#include "Logic Library/Random.h"

using namespace std;
using namespace sf; //SFML Graphics

int main()
{
    Logic::Score score{};
    auto random = Logic::Random::getInstance();
    cout << random->receiveRandom(1,4) << endl;
    Logic::World w("map.txt");
    w.attachObservers(&score);
    w.run();
//    Game::Game g;
//    g.run();
}