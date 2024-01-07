//
// Created by Qami on 11/28/2023.
//

#include "LevelState.h"
#include "../../Logic Library/Stopwatch.h"

using namespace std;

namespace Game {
LevelState::LevelState(const shared_ptr<StateManager>& context)
    : camera(getStateManager()->getCamera()), nextDirection(MOVE_LEFT), pacmanInterval(0),
      mapWidth(world.getTilemap()[0].size()), mapHeight(world.getTilemap().size()), State(context),
      world(Logic::World("map3.txt", getStateManager()->getLevel())), score(getStateManager()->getScore()) {
    unique_ptr<Logic::AbstractFactory> abstractFactory = make_unique<SingleViewFactory>();
    world.setAbstractFactory(abstractFactory);

    shared_ptr<Logic::Observer> Score = score;
    world.attachObservers(Score);
    world.getAbstractFactory()->transferShared(sharedPacmanView, sharedGhostViews, sharedCoinView, sharedFruitView,
                                               sharedWallView, sharedDoorView);
    world.initCharacters();
    world.run(PLAY);

    try {
        texture.loadFromFile(PATH_IMAGES + IMAGE_SPRITE_TEXTURES);
        wallTexture.loadFromFile(PATH_IMAGES + IMAGE_WALL_TEXTURES);
        font.loadFromFile(PATH_FONTS + FONT_MASTER);
    } catch (string& err) {
        cout << err << endl;
    }
}

void LevelState::draw(RenderWindow& w) {
    Logic::Stopwatch::getInstance()->newDeltaTime();
    scale = camera->calcScale(mapHeight + 1, mapWidth, SCALE_SIZE, w);
    scaleFruit = camera->calcScale(mapHeight + 1, mapWidth, SCALE_SIZE * 2, w);
    scaleWall = camera->calcScale(mapHeight + 1, mapWidth, WALL_SIZE, w);
    w.clear();
    drawMap(w);
    drawScore(w);
    drawLives(w);
    w.display();
}

void LevelState::drawMap(RenderWindow& w) {
    Logic::tilemap tilemap = world.getTilemap();
    entities type;
    // algorithm found on YouTube CodeNoodles:  https://www.youtube.com/watch?v=ZXnK0vlSJV8
    for (int i = 0; i < tilemap.size(); ++i) {
        for (int j = 0; j < tilemap[i].size(); ++j) {
            type = (tilemap[i][j]) ? tilemap[i][j]->getType() : EMPTY;
            if (type == WALL) {
                unsigned int index = 0;

                if (i - 1 >= 0 && tilemap[i - 1][j]) {
                    index |= (tilemap[i - 1][j]->getType() == WALL) ? 1 : 0;
                }

                if (j + 1 < tilemap[i].size() && tilemap[i][j + 1]) {
                    index |= (tilemap[i][j + 1]->getType() == WALL) ? 2 : 0;
                }

                if (i + 1 < tilemap.size() && tilemap[i + 1][j]) {
                    index |= (tilemap[i + 1][j]->getType() == WALL) ? 4 : 0;
                }

                if (j - 1 >= 0 && tilemap[i][j - 1]) {
                    index |= (tilemap[i][j - 1]->getType() == WALL) ? 8 : 0;
                }
                sharedWallView->setTexture(index);
                drawTile(w, type, {i, j});
            } else if (tilemap[i][j]) {
                drawTile(w, type, {i, j});
            }
        }
    }
}

void LevelState::drawTile(RenderWindow& w, const entities& type, const position& p) {
    static int ghostCount = 0;
    IntRect area = {0, 0, 0, 0};
    int offsetW = (w.getSize().x / 2) - (mapWidth * SCALE_SIZE) * scale.x / 2;
    Sprite tile;
    tile.setTexture(texture);
    tile.setPosition((21 + p.y * SCALE_SIZE) * scale.x, (25 + p.x * SCALE_SIZE) * scale.y);
    switch (type) {
    case PACMAN:
        area = sharedPacmanView->getTexture();
        tile.scale(scale);
        tile.setOrigin(17.5, 17.5);
        break;
    case LOSER_PACMAN:
        getStateManager()->push(LOST, getStateManager());
        break;
    case WINNER_PACMAN:
        getStateManager()->push(WON, getStateManager());
        break;
    case GHOST:
    case SCATTER_GHOST:
    case FRIGHTENED_GHOST:
    case EATEN_GHOST:
        for (const auto& g : sharedGhostViews) {
            if (g->getLocation() == p) {
                area = g->getTexture();
            }
        }
        ghostCount = (ghostCount + 1) % 4;
        tile.scale(scale);
        tile.setOrigin(18, 18);
        break;
    case COIN:
        area = sharedCoinView->getTexture();
        tile.scale(scale);
        tile.setOrigin(3.5, 3.5);
        break;
    case FRUIT:
        area = sharedFruitView->getTexture();
        tile.scale(scaleFruit);
        tile.setOrigin(17.5, 17.5);
        break;
    case WALL:
        area = sharedWallView->getTexture();
        tile.setTexture(wallTexture);
        tile.scale(scaleWall);
        tile.setOrigin(20.5, 20.5);
        break;
    case DOOR:
        area = sharedDoorView->getTexture();
        tile.setTexture(wallTexture);
        tile.scale(scaleWall);
        tile.setOrigin(20.5, 20.5);
        break;
    case EMPTY:
        break;
    }
    tile.setTextureRect(area);
    w.draw(tile);
}

void LevelState::keyPress() {

    if (Keyboard::isKeyPressed(sf::Keyboard::W) || Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        nextDirection = MOVE_UP;
    }

    else if (Keyboard::isKeyPressed(sf::Keyboard::A) || Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        nextDirection = MOVE_LEFT;
    }

    else if (Keyboard::isKeyPressed(sf::Keyboard::S) || Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        nextDirection = MOVE_DOWN;
    }

    else if (Keyboard::isKeyPressed(sf::Keyboard::D) || Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        nextDirection = MOVE_RIGHT;
    }

    else if (Keyboard::isKeyPressed(sf::Keyboard::P) || Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
        getStateManager()->push(PAUSED, getStateManager());
    }

    handlePeriod();
}

void LevelState::drawScore(RenderWindow& w) {
    Text scoreT;
    scoreT.setFont(font);
    scoreT.setString(to_string(getStateManager()->getScore()->getScore()));
    scoreT.setPosition(10, 5 + mapHeight * SCALE_SIZE * scale.x);
    scoreT.scale(scale);
    w.draw(scoreT);
}

void LevelState::drawLives(RenderWindow& w) {
    Sprite life;
    life.setTexture(texture);
    life.setTextureRect({595, 601, 24, 26});
    life.scale(scale);
    for (int oneLife = 0; oneLife < getStateManager()->getScore()->getLives(); oneLife++) {
        life.setPosition((mapWidth * SCALE_SIZE - (SCALE_SIZE + (oneLife * LIFE_OCCUPATION))) * scale.x,
                         (LIFE_DRAW_OFFSET + mapHeight * SCALE_SIZE) * scale.x);
        w.draw(life);
    }
}

void LevelState::handlePeriod() {
    auto Stopwatch = Logic::Stopwatch::getInstance();

    if (Stopwatch->totalPassed(PACMAN_SPEED, pacmanInterval)) {
        world.run(nextDirection);
    }

    for (int i = 0; i < sharedGhostViews.size(); i++) {
        if (Stopwatch->totalPassed(sharedGhostViews[i]->getSpeed(), sharedGhostViews[i]->getMovementInterval())) {
            world.movementGhost(i);
        }
    }
}
} // namespace Game