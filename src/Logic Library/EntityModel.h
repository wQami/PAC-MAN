//
// Created by Qami on 11/23/2023.
//

#ifndef PAC_MAN_ENTITYMODEL_H
#define PAC_MAN_ENTITYMODEL_H

#include "Subject.h"

namespace Logic {

    class EntityModel : private Subject{

    };

    class Ghost : private EntityModel{

    };

    class Wall : private EntityModel{

    };

    class Collectable : private EntityModel{

    };

    class Coin : private Collectable {

    };

    class Fruit : private Collectable {

    };

    class PacMan : private EntityModel{

    };

} // Logic

#endif //PAC_MAN_ENTITYMODEL_H
