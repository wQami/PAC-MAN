//
// Created by Qami on 11/23/2023.
//

#ifndef PAC_MAN_ABSTRACTFACTORY_H
#define PAC_MAN_ABSTRACTFACTORY_H

#include "EntityModel.h"
#include "Models/PacMan.h"
#include "Models/Wall.h"
#include "Models/Ghost.h"
#include "Models/Collectable.h"

namespace Logic {

    class SubjectFactory {
    public:
        virtual PacMan createPacman() = 0;
        virtual Ghost createGhost() = 0;
        virtual Collectable createCollectable() = 0;
        virtual Wall createWall() = 0;
        virtual Door createDoor() = 0;
    };

    class ModelFactory : SubjectFactory{
    public:
        PacMan createPacman() override;
        Ghost createGhost() override;
        Collectable createCollectable() override;
        Wall createWall() override;
        Door createDoor() override;
    };

} // Logic

#endif //PAC_MAN_ABSTRACTFACTORY_H
