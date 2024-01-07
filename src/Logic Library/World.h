//
// Created by Qami on 11/23/2023.
//

#ifndef PAC_MAN_WORLD_H
#define PAC_MAN_WORLD_H

#include "../global.h"
#include "AbstractFactory.h"
#include "EntityModel.h"
#include "Models/Collectable.h"
#include "Models/Ghost.h"
#include "Models/PacMan.h"
#include "Models/Wall.h"
#include "Score.h"
#include <atomic>
#include <fstream>
#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <vector>

using namespace std;

namespace Logic {

class World {
private:
    tilemap tilemap;                             // Game map
    unique_ptr<AbstractFactory> abstractFactory; // Factory for creating the models and views
    vector<shared_ptr<Ghost>> sharedGhosts;      // Shared pointers: Ghosts
    shared_ptr<PacMan> sharedPacMan;             // Shared pointer: Pacman
    shared_ptr<Coin> sharedCoin;                 // Shared pointer: Coin
    shared_ptr<Fruit> sharedFruit;               // Shared pointer: Fruit
    shared_ptr<Wall> sharedWall;                 // Shared pointer: Wall
    shared_ptr<Door> sharedDoor;                 // Shared pointer: Door
    vector<position> doorLocations;

    int level{};              // Current level of the World
    int ghostsReleased;       // Amount of Ghosts on the map
    int lastGhostInterval;    // Last interval that release a ghost
    directions lastDirection; // Last allowed direction Pac-Man moved to

public:
    // GAME-LOOP FUNCTIONS:
    explicit World(const string& fileName, int i);    // Initialize the World object [using FileReader class]
    void attachObservers(shared_ptr<Observer> Score); // Attach needed observers to the models
    void attachViews();                               // Attach needed views to the models
    void display();                                   // Display the map in console [using FileWriter class]
    void runConsole();                                // Start the game-loop for console
    void run(const events& e);                        // Start the game-loop for SFML Interface
    void eventHandler(events);                        // Handles in-game events (e.g. coin collected)
    void newRound();                                  // Initiate a new round
    void gameOver();                                  // Initiate the loss of the game
    void victory();                                   // Initiate the win of the game

    // CHARACTER FUNCTIONS
    entities moveCharacter(const shared_ptr<Ghost>& g, position p, directions d); // Move Pac-Man or the Ghosts
    void movementPacman(directions d); // Decide the movement direction Pac-Man can head
    void movementGhosts();             // Decide the movement direction for each Ghost, all Ghosts at once
    void movementGhost(int i);         // Decide the movement direction for a Ghost, only one Ghost
    void releaseGhosts();              // Release Ghosts at their respected interval
    void frightenGhosts();             // Frighten all Ghosts
    void initCharacters();             // Initializes the startlocation of the characters
    void syncCharacters();             // Makes sure the characters are on the map
    void resetCharacters();            // Resets character positions to their startpositions

    // GETTERS
    [[nodiscard]] const Logic::tilemap& getTilemap() const;
    [[nodiscard]] const unique_ptr<AbstractFactory>& getAbstractFactory() const;

    // SETTERS
    void setAbstractFactory(unique_ptr<AbstractFactory>& abstractFactory);
};

} // namespace Logic

#endif // PAC_MAN_WORLD_H
