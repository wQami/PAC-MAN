//
// Created by Qami on 11/23/2023.
//

#ifndef PAC_MAN_WORLD_H
#define PAC_MAN_WORLD_H

#include <map>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <memory>
#include "../enum.h"
#include "EntityModel.h"
#include "Models/PacMan.h"
#include "Models/Ghost.h"
#include "Models/Collectable.h"
#include "Models/Wall.h"
#include "Score.h"

using namespace std;

namespace Logic {
    class World {
    private:
        vector<vector<shared_ptr<EntityModel>>> tilemap;
        shared_ptr<PacMan> sharedPacMan;
        vector<shared_ptr<Ghost>> sharedGhosts;
        shared_ptr<Coin> sharedCoin;
        shared_ptr<Fruit> sharedFruit;
        shared_ptr<Wall> sharedWall;
        shared_ptr<Door> sharedDoor;
    public:
        explicit World(const string& fileName);
        void display();
        void run();
        void gameOver();
        void victory();
        void eventHandler(events);
        void entityToEvent(entities type);
        void attachObservers(Observer* Score);

        shared_ptr<EntityModel> entityFactory(char x);
        entities movePacman(pair<int,int> p, events e);
        void movementPacman(events e);
        void moveGhosts();
        void returnGhosts();

    };

} // Logic

#endif //PAC_MAN_WORLD_H
