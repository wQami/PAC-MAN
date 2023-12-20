//
// Created by Qami on 11/23/2023.
//

#ifndef PAC_MAN_STATE_H
#define PAC_MAN_STATE_H

#include <string>
#include <memory>
#include <stack>
using namespace std;


namespace Game {

    class State {
    private:
    public:
        State() = default;
        virtual ~State() = default;
    };
} // Game

#endif //PAC_MAN_STATE_H
