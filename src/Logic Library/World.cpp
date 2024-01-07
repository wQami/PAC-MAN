#pragma clang diagnostic push
#pragma ide diagnostic ignored "misc-no-recursion"
//
// Created by Qami on 11/23/2023.
//

#include "World.h"
#include "FileReader.h"
#include "FileWriter.h"
#include "Random.h"
#include "Stopwatch.h"
#include <cmath>
#include <unistd.h>

namespace Logic {
// class read and write file;

bool running = false;

World::World(const string& fileName, int i)
    : lastDirection(LEFT), lastGhostInterval(0), ghostsReleased(0), abstractFactory(make_unique<SingleModelFactory>()),
      level(i) {
    Stopwatch::getInstance()->reset();
    FileReader fR(fileName);
    fR.mapReader(tilemap, abstractFactory);
    abstractFactory->transferShared(sharedPacMan, sharedGhosts, sharedCoin, sharedFruit, sharedWall, sharedDoor);
    initCharacters();
}

void World::attachObservers(shared_ptr<Observer> Score) {
    sharedPacMan->attach(Score);
    for (const auto& g : sharedGhosts) {
        g->attach(Score);
    }
    sharedCoin->attach(Score);
    sharedFruit->attach(Score);

    attachViews();
}

void World::attachViews() {
    abstractFactory->viewFactory(sharedPacMan);
    for (const auto& g : sharedGhosts) {
        abstractFactory->viewFactory(g);
    }
    abstractFactory->viewFactory(sharedCoin);
    abstractFactory->viewFactory(sharedFruit);
    abstractFactory->viewFactory(sharedWall);
    abstractFactory->viewFactory(sharedDoor);
}

void World::display() { Logic::FileWriter::mapOut(tilemap); }

void World::runConsole() {
    events event;
    char input;
    running = true;
    cout << "\nX to exit.\nP to play" << endl;

    while (running) {
        cin >> input;

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
            running = false;
            event = NONE;
            break;

        default:
            event = NONE;
            cout << "Press the right button." << endl;
            break;
        }
        if (event != PLAY)
            movementGhosts();
        run(event);
        display();
        cout << "\nX to exit.\nWASD for movements" << endl;
    }
}

void World::run(const events& event) {
    if (sharedDoor->itsTime() && sharedDoor->isClosed()) {
        sharedDoor->open();
        Stopwatch::getInstance()->reset();
    }
    if (!sharedGhosts[sharedGhosts.size() - 1]->hasStarted())
        releaseGhosts();

    eventHandler(event);

    if (event != PLAY)
        syncCharacters();
}

void World::eventHandler(events e) {
    switch (e) {

    case MOVE_UP:
    case MOVE_DOWN:
    case MOVE_LEFT:
    case MOVE_RIGHT:
        movementPacman(eventToDirections(e));
        if (sharedPacMan->getType() != PACMAN)
            break; // Continues down to the PLAY event, preventing repetitive code

    case PLAY:
        break;

    case COIN_COLLECTED:
        if (sharedCoin.use_count() == 1) {
            eventHandler(VICTORY);
            break;
        }
        sharedCoin->notify();
        break;

    case FRUIT_EATEN:
        sharedFruit->notify();
        frightenGhosts();
        Stopwatch::getInstance()->reset();
        Stopwatch::getInstance()->resetFright();
        break;

    case ATTACKED:
        sharedPacMan->hit();
        if (sharedPacMan->getType() == LOSER_PACMAN) {
            eventHandler(GAME_OVER);
            break;
        }
        newRound();
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

void World::movementPacman(directions d) {
    eventHandler(entityToEvents(moveCharacter(nullptr, possibleDirections[d], d)));
}

void World::movementGhost(int i) {
    shared_ptr<Ghost> current = sharedGhosts[i];
    entities typeGhost = current->getType();
    entities typeGhostAfter;
    entities before = current->getType();

    directions choice = current->movement(tilemap, sharedPacMan, sharedGhosts[0]->getLocation());
    entities type = moveCharacter(current, possibleDirections[choice], choice);

    if (type == PACMAN && (typeGhost == GHOST || typeGhost == SCATTER_GHOST)) {
        eventHandler(entityToEvents(type));
    }

    typeGhostAfter = current->getType();
    if (before != typeGhostAfter && typeGhostAfter != FRIGHTENED_GHOST && i == 3)
        Stopwatch::getInstance()->reset();
    syncCharacters();
    sharedGhosts[i]->notify();
}

void World::movementGhosts() {
    entities before = sharedGhosts[0]->getType();
    for (auto& g : sharedGhosts) {
        if (g->hasStarted()) {
            directions choice = g->movement(tilemap, sharedPacMan, sharedGhosts[0]->getLocation());
            entities type = moveCharacter(g, possibleDirections[choice], choice);
            if (type == PACMAN && (g->getType() == GHOST || g->getType() == SCATTER_GHOST)) {
                eventHandler(entityToEvents(type));
            }
        }
    }

    if (before != sharedGhosts[0]->getType() && sharedGhosts[0]->getType() != FRIGHTENED_GHOST)
        Stopwatch::getInstance()->reset();
    syncCharacters();
}

entities World::moveCharacter(const shared_ptr<Ghost>& g, position p, directions d) {
    int pmX = (g == nullptr) ? sharedPacMan->getLocation().x : g->getLocation().x;
    int pmY = (g == nullptr) ? sharedPacMan->getLocation().y : g->getLocation().y;

    sharedEntityModel underGhost;
    sharedEntityModel nextEntity = tilemap[pmX + p.x][pmY + p.y];
    entities nextType = (nextEntity) ? nextEntity->getType() : EMPTY;
    bool eatable = !(nextEntity) || nextEntity->isEatable();
    bool eatableGhost = (nextType == DOOR && sharedDoor->getValue() == 1);

    if (eatable || eatableGhost) {
        if (g == nullptr && eatable) {
            sharedPacMan->move(d);
            lastDirection = d;
            if (nextType == FRIGHTENED_GHOST) {
                tilemap[pmX + p.x][pmY + p.y]->setType(EATEN_GHOST);
            }

            tilemap[pmX][pmY].reset();
            tilemap[pmX + p.x][pmY + p.y] = sharedPacMan;
        } else if (g != nullptr && g->hasStarted()) {
            g->move(d);

            underGhost = g->getUnderGhost();
            g->setUnderGhost(nextEntity);

            tilemap[pmX][pmY] = underGhost;
            tilemap[pmX + p.x][pmY + p.y] = g;
            if (nextType == DOOR)
                g->gotOutOfCage();
            if (g->getLocation() == sharedPacMan->getLocation())
                nextType = PACMAN;
            if (g->getLocation() == sharedPacMan->getLocation() && g->getType() == FRIGHTENED_GHOST)
                g->setType(EATEN_GHOST);
        }
    }

    return (d != lastDirection && g == nullptr) ? moveCharacter(g, possibleDirections[lastDirection], lastDirection)
                                                : nextType;
}

void World::frightenGhosts() {
    for (const auto& g : sharedGhosts) {
        g->frighten();
        g->setDirection(!g->getDirection());
    }
}

void World::resetCharacters() {
    for (const auto& g : sharedGhosts) {
        tilemap[g->getLocation().x][g->getLocation().y] = g->getUnderGhost();
        tilemap[g->getStartLocation().x][g->getStartLocation().y] = g;
        g->resetPosition();
    }

    tilemap[sharedPacMan->getLocation().x][sharedPacMan->getLocation().y].reset();
    tilemap[sharedPacMan->getStartLocation().x][sharedPacMan->getStartLocation().y] = sharedPacMan;
    sharedPacMan->resetPosition();
}

void World::newRound() {
    resetCharacters();
    sharedDoor->close();
    ghostsReleased = 0;
    Stopwatch::getInstance()->reset();
}

void World::gameOver() {
    cout << "GAME OVER!" << endl;
    sharedPacMan->setType(LOSER_PACMAN);
    cout << "\nPress X to exit" << endl;
    running = false;
}

void World::victory() {
    cout << "\nWINNER WINNER CHICKEN DINNER!" << endl << endl;
    sharedPacMan->setType(WINNER_PACMAN);
    cout << "\nPress X to exit" << endl;
    running = false;
}

void World::syncCharacters() {
    for (auto t : doorLocations) {
        tilemap[t.x][t.y] = sharedDoor;
    }

    for (const auto& g : sharedGhosts) {
        tilemap[g->getLocation().x][g->getLocation().y] = g;
    }
    tilemap[sharedPacMan->getLocation().x][sharedPacMan->getLocation().y] = sharedPacMan;
}

const tilemap& World::getTilemap() const { return tilemap; }

void World::setAbstractFactory(unique_ptr<AbstractFactory>& aF) { abstractFactory = std::move(aF); }

void World::initCharacters() {
    int ghostCount = 0;
    int rowSize = tilemap[0].size();
    int columnSize = tilemap.size();
    vector<position> scatterTargets = {{0, rowSize}, {0, 0}, {columnSize, rowSize}, {columnSize, 0}};

    doorLocations.clear();
    for (int i = 0; i < tilemap.size(); i++) {
        for (int j = 0; j < tilemap[i].size(); j++) {
            if (tilemap[i][j] && tilemap[i][j]->getType() == PACMAN) {
                sharedPacMan->setLocation({i, j});
            }

            if (tilemap[i][j] && tilemap[i][j]->getType() == SCATTER_GHOST) {
                sharedGhosts[ghostCount]->setLocation({i, j});
                sharedGhosts[ghostCount]->setScatterTarget(scatterTargets[sharedGhosts[ghostCount]->getColor()]);
                sharedGhosts[ghostCount]->setLevel(level);
                ghostCount++;
            }

            if (tilemap[i][j] && tilemap[i][j]->getType() == DOOR) {
                doorLocations.push_back({i, j});
            }
        }
    }
}

const unique_ptr<AbstractFactory>& World::getAbstractFactory() const { return ::move(abstractFactory); }

void World::releaseGhosts() {
    if (ghostsReleased == 0) {
        if (Stopwatch::getInstance()->totalPassed(DURATION_OPEN_DOOR, lastGhostInterval)) {
            sharedGhosts[0]->roundStart();
            sharedGhosts[1]->roundStart();
            ghostsReleased = 2;
        }
    } else {
        if (Stopwatch::getInstance()->totalPassed(DURATION_NEXT_GHOST, lastGhostInterval) &&
            ghostsReleased < sharedGhosts.size()) {
            sharedGhosts[ghostsReleased]->roundStart();
            ghostsReleased++;
        }
    }
}
} // namespace Logic
#pragma clang diagnostic pop