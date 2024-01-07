//
// Created by Qami on 11/23/2023.
//

#ifndef PAC_MAN_ENTITYVIEW_H
#define PAC_MAN_ENTITYVIEW_H

#include "../Logic Library/EntityModel.h"
#include "../Logic Library/Observer.h"
#include "../global.h"
#include "../globalGame.h"
#include "SFML/Graphics.hpp"
#include <memory>
#include <vector>

using namespace std;
using namespace sf;
namespace Game {

class EntityView : public Logic::Observer {
private:
public:
    EntityView();
    void update(Logic::EntityModel* subject) override;
};

typedef shared_ptr<EntityView> sharedEntityView;

class PacMan : public EntityView {
private:
    int speed;
    int lastTexture;
    int lastTextureChange;
    directions direction;
    position prevlocation;
    position location;
    Vector2f drawlocation;

    IntRect spriteFull;
    vector<pair<IntRect, IntRect>> moves;
    vector<IntRect> currentMoves;

public:
    PacMan();

    void update(Logic::EntityModel* subject) override;
    [[nodiscard]] const position& getLocation() const;
    [[nodiscard]] const position& getPrevlocation() const;
    [[nodiscard]] const directions& getDirection() const;
    void draw(RenderWindow& W, const Texture& texture);
    IntRect getTexture();
};

class Ghost : public EntityView {
private:
    int speed;
    int lastTexture;
    int lastTextureChange;
    int movementInterval;

    entities type;
    colors color;
    directions direction;
    position prevlocation;
    position location;
    Vector2f drawlocation;

    vector<pair<IntRect, IntRect>> moves;
    vector<IntRect> movesEaten;
    pair<IntRect, IntRect> spriteFright;
    pair<IntRect, IntRect> spriteFrightRunningOut;
    pair<IntRect, IntRect> currentMoves;

public:
    Ghost();
    explicit Ghost(int i);
    void update(Logic::EntityModel* subject) override;

    [[nodiscard]] const position& getLocation() const;
    IntRect getTexture();

    [[nodiscard]] int& getSpeed();
    [[nodiscard]] int& getMovementInterval();
};

class Coin : public EntityView {
private:
    IntRect texture;

public:
    Coin();

    [[nodiscard]] const IntRect& getTexture() const;
    void update(Logic::EntityModel* subject) override;
};

class Fruit : public EntityView {
private:
    IntRect texture;

public:
    Fruit();
    void update(Logic::EntityModel* subject) override;
    const IntRect& getTexture() const;
};

class Wall : public EntityView {
    IntRect texture;

public:
    Wall();
    void update(Logic::EntityModel* subject) override;
    [[nodiscard]] const IntRect& getTexture() const;
    void setTexture(const int index);
};

class Door : public EntityView {
    IntRect texture;

public:
    Door();
    void update(Logic::EntityModel* subject) override;
    [[nodiscard]] const IntRect& getTexture() const;
};

} // namespace Game

#endif // PAC_MAN_ENTITYVIEW_H
