//
// Created by Qami on 11/28/2023.
//

#ifndef PAC_MAN_OBSERVER_H
#define PAC_MAN_OBSERVER_H

#include "Observer.h"

namespace Logic {

    class EntityModel;

    class Observer {
    public:
        ~Observer() = default;
        virtual void update(EntityModel *subject) = 0;
    };

} // Logic

#endif //PAC_MAN_OBSERVER_H
