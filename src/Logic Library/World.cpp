#pragma clang diagnostic push
#pragma ide diagnostic ignored "misc-no-recursion"
//
// Created by Qami on 11/23/2023.
//

#include "World.h"

namespace Logic {
    World::World(const string& fileName) {
        std::ifstream map;
        map.open("resources/tilemaps/"+ fileName);
        string line;

        try {
            int i = 0;
            while (getline(map, line)){
                vector<shared_ptr<EntityModel>> characters;
                int j = 0;
                for(char c : line){
                    characters.push_back(entityFactory(c));

                    if(c == 'O'){
                        sharedPacMan->setLocation(make_pair(i,j));
                    }

                    if(c == 'g'){
                        sharedGhosts.back()->setLocation(make_pair(i,j));
                    }
                    j++;
                }
                i++;
                tilemap.push_back(characters);
                characters.clear();
            }
        }
        catch (string &e) {
            cout << "File not found: " << e << endl;
        }
    }

    void World::display() {
        for(auto & i : tilemap){
            for(const auto & j : i){
                if(j) {
                    switch (j->getType()) {
                        case LOSER_PACMAN:
                        case WINNER_PACMAN:
                        case PACMAN:
                            cout << 'O';
                            break;
                        case GHOST:
                            cout << 'g';
                            break;
                        case EATABLEGHOST:
                            cout << 'w';
                            break;
                        case COIN:
                            cout << '-';
                            break;
                        case FRUIT:
                            cout << 'y';
                            break;
                        case WALL:
                            cout << 'x';
                            break;
                        case DOOR:
                            cout << '=';
                            break;
                        case EMPTY:
                            cout << ' ';
                            break;
                    }
                } else {
                    cout << ' ';
                }
            }
            cout << endl;
        }
    }

    void World::run() {
        events event;
        char input;
        bool run = true;
        cout << "\nX to exit.\nP to play" << endl;

        while(run) {
            cin >> input;
            moveGhosts();
            switch (toupper(input)) {
                case 'P':
                    event = PLAY;
                    break;

                case 'W':
                    event = MOVE_UP;
                    break;

                case 'A':
                    event = MOVE_LEFT;
                    break;

                case 'S':
                    event = MOVE_DOWN;
                    break;

                case 'D':
                    event = MOVE_RIGHT;
                    break;

                case 'X':
                    run = false;
                    event = NONE;
                    break;

                default:
                    event = NONE;
                    cout << "Press the right button." << endl;
                    break;
            }
            eventHandler(event);
        }
    }

    void World::eventHandler(events e) {
        switch(e){
            case PLAY:
                display();
                cout << "\nX to exit.\nWASD for movements" << endl;
                break;

            case MOVE_UP:
            case MOVE_DOWN:
            case MOVE_LEFT:
            case MOVE_RIGHT:
                movementPacman(e);

                if(sharedPacMan->getType() != PACMAN) break;
                sharedPacMan->notify();

                display();
                cout << "\nX to exit.\nWASD for movements" << endl;
                break;

            case COIN_COLLECTED:
                if(sharedCoin.use_count() == 1){
                    eventHandler(VICTORY);
                    break;
                }
                sharedCoin->notify();
                break;

            case FRUIT_EATEN:
                sharedFruit->notify();
                for(const auto& g : sharedGhosts){
                    g->setEatable(true);
                }
                break;

            case GHOST_EATEN:

                break;

            case GHOST_ATTACK:
                sharedPacMan->notify();
                break;

            case GAME_OVER:
                gameOver();
                break;

            case VICTORY:
                victory();
                break;

            case NONE:
                break;
        }
    }

    shared_ptr<EntityModel> World::entityFactory(char c) {
        shared_ptr<EntityModel> created;
        switch(c){
            case 'x':
                if(!sharedWall) {
                    sharedWall = make_shared<Wall>();
                }
                created = sharedWall;
                break;

            case 'O':
                if(!sharedPacMan) {
                    sharedPacMan = make_shared<PacMan>();
                }
                created = sharedPacMan;
                break;

            case 'y':
                if(!sharedFruit){
                    sharedFruit = make_shared<Fruit>();
                }
                created = sharedFruit;
                break;

            case 'g':
                sharedGhosts.push_back(make_shared<Ghost>(static_cast<colors>(sharedGhosts.size() % 7)));
                created = sharedGhosts.back();
                break;

            case ' ':
                created = nullptr;
                break;

            case '-':
                if(!sharedCoin){
                    sharedCoin = make_shared<Coin>();
                }
                created = sharedCoin;
                break;

            case '=':
                if(!sharedDoor){
                    sharedDoor = make_shared<Door>();
                }
                created = sharedDoor;
                break;

            default:
                cout << "Wrong input, character gets skipped. Input: " << c << endl;
                created = nullptr;
                break;
        }

        return created;
    }

    void World::movementPacman(events e) {
        entities type = EMPTY;
        switch (e) {
            case MOVE_UP:
                type = movePacman(make_pair(-1,0),e);
                break;

            case MOVE_DOWN:
                type = movePacman(make_pair(1,0),e);
                break;

            case MOVE_LEFT:
                type = movePacman(make_pair(0,-1),e);
                break;
            case MOVE_RIGHT:
                type = movePacman(make_pair(0,1),e);
                break;

            default:
                cout << "Not a move!" << endl;
                break;
        }
        entityToEvent(type);
    }

    entities World::movePacman(pair<int, int> p, events e) {
        int pmX = sharedPacMan->getLocation().first;
        int pmY = sharedPacMan->getLocation().second;

        entities type = (tilemap[pmX + p.first][pmY + p.second]) ? tilemap[pmX + p.first][pmY + p.second]->getType() : EMPTY;
        bool eatable = !(tilemap[pmX + p.first][pmY + p.second]) || tilemap[pmX + p.first][pmY + p.second]->isEatable();
        if(eatable){
            sharedPacMan->move(e);
            tilemap[pmX + p.first][pmY + p.second] = sharedPacMan;
            tilemap[pmX][pmY].reset();
        }

        return type;
    }

    void World::entityToEvent(entities type) {
        switch (type) {
            case COIN:
                eventHandler(COIN_COLLECTED);
                break;
            case FRUIT:
                eventHandler(FRUIT_EATEN);
                break;
            case EATABLEGHOST:
                eventHandler(GHOST_EATEN);
                break;
            default:
                break;
        }
    }

    void World::moveGhosts() {

    }

    void World::returnGhosts() {

    }

    void World::gameOver() {
        cout << "GAME OVER!" << endl;
        sharedPacMan->setType(LOSER_PACMAN);
        sharedPacMan->notify();
    }

    void World::victory() {
        cout << "\nWINNER WINNER CHICKEN DINNER!" << endl << endl;
        sharedPacMan->setType(WINNER_PACMAN);
        sharedPacMan->notify();
        cout << "\nPress X to exit" << endl;
    }

    void World::attachObservers(Observer* Score) {
        sharedPacMan->attach(Score);
        sharedCoin->attach(Score);
        for(const auto& g : sharedGhosts){
            g->attach(Score);
        }
        sharedFruit->attach(Score);
    }
} // Logic
#pragma clang diagnostic pop