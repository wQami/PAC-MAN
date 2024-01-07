//
// Created by Qami on 11/23/2023.
//

#ifndef PAC_MAN_ENTITYMODEL_H
#define PAC_MAN_ENTITYMODEL_H

#include "Subject.h"

namespace Logic {

class EntityModel : public Subject {
private:
    list<shared_ptr<Observer>> _observers;
    entities type;
    int value;
    bool eatable{};
    position location;
    directions direction;

public:
    EntityModel();
    explicit EntityModel(EntityModel* pModel);

    [[nodiscard]] entities getType() const;
    [[nodiscard]] bool isEatable() const;
    [[nodiscard]] int getValue() const;

    [[nodiscard]] virtual directions getDirection() const;
    [[nodiscard]] virtual const position& getLocation() const;

    void setType(entities type);
    void setEatable(bool eatable);
    void setValue(int value);
    void setLocation(position p);
    void setDirection(directions d);

    void attach(shared_ptr<Observer>& obs) override;
    void detach(shared_ptr<Observer>& obs) override;
    void notify() override;
};

typedef shared_ptr<EntityModel> sharedEntityModel;
typedef vector<vector<sharedEntityModel>> tilemap;
} // namespace Logic

#endif // PAC_MAN_ENTITYMODEL_H
