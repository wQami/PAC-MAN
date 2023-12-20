//
// Created by Qami on 11/23/2023.
//

#ifndef PAC_MAN_SUBJECT_H
#define PAC_MAN_SUBJECT_H

#include <string>
#include <list>
#include <memory>
#include "Observer.h"
#include "../enum.h"
using namespace std;

namespace Logic {

    class Subject {
    public:
        Subject() = default;
        ~Subject();
        virtual void attach(Observer* &obs) = 0;
        virtual void detach(Observer* &obs) = 0;
        virtual void notify() = 0;
    };



} // Logic

#endif //PAC_MAN_SUBJECT_H
