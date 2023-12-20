//
// Created by Qami on 12/2/2023.
//

#ifndef PAC_MAN_GHOST_H
#define PAC_MAN_GHOST_H

#include "../EntityModel.h"

namespace Logic {

    class Ghost : public EntityModel{
    private:
        colors color;
        pair<int,int> startLocation;
        pair<int,int> location;
    public:
        Ghost();
        explicit Ghost(colors c);

        [[nodiscard]] colors getColor() const;
        [[nodiscard]] const pair<int, int> &getStartLocation() const;
        [[nodiscard]] const pair<int, int> &getLocation() const;

        void setColor(colors color);
        void setLocation(const pair<int, int> &location);
    };


} // Logic

#endif //PAC_MAN_GHOST_H
