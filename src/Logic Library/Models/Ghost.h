//
// Created by Qami on 12/2/2023.
//

#ifndef PAC_MAN_GHOST_H
#define PAC_MAN_GHOST_H

#include "../EntityModel.h"
#include "PacMan.h"
#include <vector>

namespace Logic {

class Ghost : public EntityModel {
private:
    colors color;
    position startLocation{};
    position scatterTarget{};
    sharedEntityModel underGhost;
    bool outOfCage;
    bool startRound;
    int modeIndex;
    int level;

    // Direction is used here as the direction where the ghost arrived from.
public:
    Ghost();
    explicit Ghost(int i);

    [[nodiscard]] colors getColor() const;
    [[nodiscard]] const position& getStartLocation() const;
    [[nodiscard]] const position& getLocation() const override;
    [[nodiscard]] const sharedEntityModel& getUnderGhost() const;
    [[nodiscard]] bool isOutOfCage() const;
    [[nodiscard]] bool hasStarted() const;

    void setLocation(const position& location);
    void setScatterTarget(const position& scatterTarget);
    void setUnderGhost(const sharedEntityModel& uG);
    void setLevel(const int& l);

    void gotOutOfCage();
    void backInCage();
    void roundStart();
    void roundWaitTurn();
    void frighten();

    directions movement(sharedmap& tilemap, const shared_ptr<PacMan>& pacMan, const position& blinky);
    position targetLocation(const position& target, const directions& pacManDirection, const position& blinky);
    directions decideDirection(sharedmap& tilemap, const position& targetLocation) const;
    directions calculateFright(sharedmap& tilemap, directions d) const;
    void move(directions e);
    void changeMode();
    void resetPosition();
};

} // namespace Logic

#endif // PAC_MAN_GHOST_H
