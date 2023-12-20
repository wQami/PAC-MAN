//
// Created by Qami on 12/2/2023.
//

#ifndef PAC_MAN_PACMAN_H
#define PAC_MAN_PACMAN_H

#include "../EntityModel.h"

namespace Logic {

    class PacMan : public EntityModel{
    private:
        pair<int,int> startLocation;
        pair<int,int> location;
    public:
        PacMan();

        [[nodiscard]] const pair<int, int> &getStartLocation() const;
        [[nodiscard]] const pair<int, int> &getLocation() const;
        void setLocation(const pair<int, int> &location);
        void move(events);
        void hit();
    };

} // Logic

#endif //PAC_MAN_PACMAN_H
