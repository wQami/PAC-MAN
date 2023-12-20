//
// Created by Qami on 12/2/2023.
//

#ifndef PAC_MAN_COLLECTABLE_H
#define PAC_MAN_COLLECTABLE_H

#include "../EntityModel.h"

namespace Logic {

    class Collectable : public EntityModel{
    private:
    public:
        Collectable();
    };

    class Coin : public Collectable {
    private:
    public:
        Coin();
        void notify() override;
    };

    class Fruit : public Collectable {
    private:
    public:
        Fruit();
        void notify() override;
    };

} // Logic

#endif //PAC_MAN_COLLECTABLE_H
