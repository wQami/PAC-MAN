//
// Created by Qami on 11/23/2023.
//

#ifndef PAC_MAN_STATEMANAGER_H
#define PAC_MAN_STATEMANAGER_H
#include "Camera.h"
#include "StateFactory.h"
#include <stack>
using namespace std;

namespace Game {
class StateManager {
private:
    int level;
    shared_ptr<Logic::Score> score;
    shared_ptr<Camera> camera;
    stack<State*> stateManager;

public:
    StateManager();
    void pop();
    void push(const states& s, const shared_ptr<StateManager>& StateManager);
    int size();
    State* top();

    [[nodiscard]] const shared_ptr<Logic::Score>& getScore() const;
    [[nodiscard]] const shared_ptr<Camera>& getCamera() const;
    [[nodiscard]] int& getLevel();
    void incLevel();
    void setLevel(int level);
    void resetStats();
};

} // namespace Game

#endif // PAC_MAN_STATEMANAGER_H
