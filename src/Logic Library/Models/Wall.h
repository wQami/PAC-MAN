//
// Created by Qami on 12/2/2023.
//

#ifndef PAC_MAN_WALL_H
#define PAC_MAN_WALL_H

#include "../EntityModel.h"

namespace Logic {

    class Wall : public EntityModel{
    private:
    public:
        Wall();
    };

    class Door : public Wall{
    private:
        bool isOpen{};
    public:
        Door();
        void open();
        void close();
    };

} // Logic

#endif //PAC_MAN_WALL_H
