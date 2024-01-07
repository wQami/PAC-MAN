//
// Created by Qami on 11/23/2023.
//

#ifndef PAC_MAN_CONCRETEFACTORY_H
#define PAC_MAN_CONCRETEFACTORY_H

#include "../Logic Library/AbstractFactory.h"

namespace Game {

class ViewFactory : public Logic::AbstractFactory {
public:
    shared_ptr<PacMan> createPacmanView() override;
    shared_ptr<Ghost> createGhostView() override;
    shared_ptr<Ghost> createGhostView(int i) override;
    shared_ptr<Coin> createCoinView() override;
    shared_ptr<Fruit> createFruitView() override;
    shared_ptr<Wall> createWallView() override;
    shared_ptr<Door> createDoorView() override;

    void viewFactory(const Logic::sharedEntityModel& em) override;

    ~ViewFactory() override = default;

    shared_ptr<Logic::PacMan> createPacman() override;
    shared_ptr<Logic::Ghost> createGhost() override;
    shared_ptr<Logic::Ghost> createGhost(int i) override;
    shared_ptr<Logic::Coin> createCoin() override;
    shared_ptr<Logic::Fruit> createFruit() override;
    shared_ptr<Logic::Wall> createWall() override;
    shared_ptr<Logic::Door> createDoor() override;
    Logic::sharedEntityModel modelFactory(char c) override;
};

class SingleViewFactory : public ViewFactory {
private:
    shared_ptr<PacMan> sharedPacManView;
    vector<shared_ptr<Ghost>> sharedGhostViews;
    shared_ptr<Coin> sharedCoinView;
    shared_ptr<Fruit> sharedFruitView;
    shared_ptr<Wall> sharedWallView;
    shared_ptr<Door> sharedDoorView;

public:
    void viewFactory(const Logic::sharedEntityModel& em) final;

    void transferShared(shared_ptr<Logic::PacMan>& p, vector<shared_ptr<Logic::Ghost>>& g, shared_ptr<Logic::Coin>& c,
                        shared_ptr<Logic::Fruit>& f, shared_ptr<Logic::Wall>& w, shared_ptr<Logic::Door>& d) final;

    ~SingleViewFactory() override = default;

    void transferShared(shared_ptr<PacMan>& p, vector<shared_ptr<Ghost>>& g, shared_ptr<Coin>& c, shared_ptr<Fruit>& f,
                        shared_ptr<Wall>& w, shared_ptr<Door>& d) final;
};

} // namespace Game

#endif // PAC_MAN_CONCRETEFACTORY_H
