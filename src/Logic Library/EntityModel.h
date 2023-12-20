//
// Created by Qami on 11/23/2023.
//

#ifndef PAC_MAN_ENTITYMODEL_H
#define PAC_MAN_ENTITYMODEL_H

#include "Subject.h"

namespace Logic {

    class EntityModel : public Subject{
    private:
        list<Observer*> _observers;
        entities type;
        int value;
        bool eatable{};
    public:
        EntityModel();
        explicit EntityModel(EntityModel *pModel);

        [[nodiscard]] entities getType() const;
        [[nodiscard]] bool isEatable() const;
        [[nodiscard]] int getValue() const;

        void setType(entities type);
        void setEatable(bool eatable);
        void setValue(int value);

        void attach(Observer* &obs) override;
        void detach(Observer* &obs) override;
        void notify() override;
    };
} // Logic

#endif //PAC_MAN_ENTITYMODEL_H
