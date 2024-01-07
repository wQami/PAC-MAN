#include "Game Representation/Game.h"
#include "Logic Library/Random.h"
#include "Logic Library/Score.h"
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;
using namespace sf; // SFML Graphics

int main() {
    //    Logic::World w("map.txt",5);
    //    shared_ptr<Logic::Observer> observer = make_shared<Logic::Score>();
    //    w.attachObservers(observer);
    //    w.runConsole();
    Game::Game g;
    g.run();
}