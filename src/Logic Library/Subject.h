//
// Created by Qami on 11/23/2023.
//

#ifndef PAC_MAN_SUBJECT_H
#define PAC_MAN_SUBJECT_H

#include "../global.h"
#include "../globalGame.h"
#include "Observer.h"
#include <list>
#include <memory>
#include <string>
using namespace std;

namespace Logic {

class Subject {
public:
    Subject() = default;
    ~Subject();
    virtual void attach(shared_ptr<Observer>& obs) = 0;
    virtual void detach(shared_ptr<Observer>& obs) = 0;
    virtual void notify() = 0;
};

} // namespace Logic

#endif // PAC_MAN_SUBJECT_H
