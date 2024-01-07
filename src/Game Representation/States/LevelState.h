//
// Created by Qami on 11/28/2023.
//

#ifndef PAC_MAN_LEVELSTATE_H
#define PAC_MAN_LEVELSTATE_H

#include "../../Logic Library/World.h"
#include "../Camera.h"
#include "../ConcreteFactory.h"
#include "../State.h"
#include "../StateManager.h"

namespace Game {

class LevelState : public State {
private:
    shared_ptr<Camera> camera;
    shared_ptr<Logic::Score> score;
    Logic::World world;

    shared_ptr<PacMan> sharedPacmanView;
    vector<shared_ptr<Ghost>> sharedGhostViews;
    shared_ptr<Coin> sharedCoinView;
    shared_ptr<Fruit> sharedFruitView;
    shared_ptr<Wall> sharedWallView;
    shared_ptr<Door> sharedDoorView;

    Font font;
    Texture texture;
    Texture wallTexture;
    events nextDirection;

    Vector2f scale;
    Vector2f scaleFruit;
    Vector2f scaleWall;

    int pacmanInterval;
    unsigned long long mapWidth;
    unsigned long long mapHeight;

public:
    explicit LevelState(const shared_ptr<StateManager>& context);

    void draw(RenderWindow& w) override;
    void drawMap(RenderWindow& w);
    void drawTile(RenderWindow& w, const entities& type, const position& p);
    void drawScore(RenderWindow& w);
    void drawLives(RenderWindow& w);
    void keyPress() override;

    void handlePeriod() override;
};

} // namespace Game

#endif // PAC_MAN_LEVELSTATE_H
