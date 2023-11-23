//
// Created by Qami on 11/23/2023.
//

#ifndef PAC_MAN_ENTITYVIEW_H
#define PAC_MAN_ENTITYVIEW_H

#include "../Logic Library/Observer.h"

namespace Game {

    class EntityView : private Logic::Observer {

    };

    class PacMan : private EntityView {

    };

    class Ghost : private EntityView {

    };

    class Coin : private EntityView {

    };

    class Fruit : private EntityView {

    };

    class Wall : private EntityView {

    };

} // Game

#endif //PAC_MAN_ENTITYVIEW_H
