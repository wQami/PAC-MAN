//
// Created by Qami on 12/2/2023.
//

#ifndef PAC_MAN_PACMAN_H
#define PAC_MAN_PACMAN_H

#include "../EntityModel.h"

namespace Logic {

    class PacMan : public EntityModel {
    private:
        position startLocation{};
        sf::Vector2f drawLocation;
        // Direction is used here as the direction Pac-Man is facing
    public:
        PacMan();

        [[nodiscard]] const position &getStartLocation() const;

        [[nodiscard]] const position &getLocation() const;

        [[nodiscard]] directions getDirection() const override;

        void setLocation(const position &location);

        void move(directions);

        void hit();

        void resetPosition();
    };

} // Logic

#endif //PAC_MAN_PACMAN_H
