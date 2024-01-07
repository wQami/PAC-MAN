//
// Created by Qami on 11/23/2023.
//

#ifndef PAC_MAN_ABSTRACTFACTORY_H
#define PAC_MAN_ABSTRACTFACTORY_H

#include "EntityModel.h"
#include "Models/Collectable.h"
#include "Models/Ghost.h"
#include "Models/PacMan.h"
#include "Models/Wall.h"

#include "../Game Representation/EntityView.h"

namespace Logic {

class AbstractFactory {
public:
    virtual ~AbstractFactory() = default;
    virtual shared_ptr<PacMan> createPacman() = 0;
    virtual shared_ptr<Ghost> createGhost() = 0;
    virtual shared_ptr<Ghost> createGhost(int i) = 0;
    virtual shared_ptr<Coin> createCoin() = 0;
    virtual shared_ptr<Fruit> createFruit() = 0;
    virtual shared_ptr<Wall> createWall() = 0;
    virtual shared_ptr<Door> createDoor() = 0;

    virtual shared_ptr<Game::PacMan> createPacmanView() = 0;
    virtual shared_ptr<Game::Ghost> createGhostView() = 0;
    virtual shared_ptr<Game::Ghost> createGhostView(int i) = 0;
    virtual shared_ptr<Game::Coin> createCoinView() = 0;
    virtual shared_ptr<Game::Fruit> createFruitView() = 0;
    virtual shared_ptr<Game::Wall> createWallView() = 0;
    virtual shared_ptr<Game::Door> createDoorView() = 0;

    virtual sharedEntityModel modelFactory(char c) = 0;
    virtual void viewFactory(const Logic::sharedEntityModel& em) = 0;

    virtual void transferShared(shared_ptr<PacMan>& p, vector<shared_ptr<Ghost>>& g, shared_ptr<Coin>& c,
                                shared_ptr<Fruit>& f, shared_ptr<Wall>& w, shared_ptr<Door>& d) = 0;
    virtual void transferShared(shared_ptr<Game::PacMan>& p, vector<shared_ptr<Game::Ghost>>& g,
                                shared_ptr<Game::Coin>& c, shared_ptr<Game::Fruit>& f, shared_ptr<Game::Wall>& w,
                                shared_ptr<Game::Door>& d) = 0;
};

class ModelFactory : public AbstractFactory {
public:
    shared_ptr<PacMan> createPacman() override;
    shared_ptr<Ghost> createGhost() override;
    shared_ptr<Ghost> createGhost(int i) override;
    shared_ptr<Coin> createCoin() override;
    shared_ptr<Fruit> createFruit() override;
    shared_ptr<Wall> createWall() override;
    shared_ptr<Door> createDoor() override;
    sharedEntityModel modelFactory(char c) override;

    // Functions below return nullptr.

    shared_ptr<Game::PacMan> createPacmanView() override;
    shared_ptr<Game::Ghost> createGhostView() override;
    shared_ptr<Game::Ghost> createGhostView(int i) override;
    shared_ptr<Game::Coin> createCoinView() override;
    shared_ptr<Game::Fruit> createFruitView() override;
    shared_ptr<Game::Wall> createWallView() override;
    shared_ptr<Game::Door> createDoorView() override;
    void viewFactory(const Logic::sharedEntityModel& em) override;
};

class SingleModelFactory : public ModelFactory {
private:
    shared_ptr<PacMan> sharedPacMan;
    vector<shared_ptr<Ghost>> sharedGhosts;
    shared_ptr<Coin> sharedCoin;
    shared_ptr<Fruit> sharedFruit;
    shared_ptr<Wall> sharedWall;
    shared_ptr<Door> sharedDoor;

public:
    sharedEntityModel modelFactory(char c) override;
    void transferShared(shared_ptr<PacMan>& p, vector<shared_ptr<Ghost>>& g, shared_ptr<Coin>& c, shared_ptr<Fruit>& f,
                        shared_ptr<Wall>& w, shared_ptr<Door>& d) override;

    ~SingleModelFactory() override = default;

    void transferShared(shared_ptr<Game::PacMan>& p, vector<shared_ptr<Game::Ghost>>& g, shared_ptr<Game::Coin>& c,
                        shared_ptr<Game::Fruit>& f, shared_ptr<Game::Wall>& w, shared_ptr<Game::Door>& d) override;
};

} // namespace Logic

#endif // PAC_MAN_ABSTRACTFACTORY_H
