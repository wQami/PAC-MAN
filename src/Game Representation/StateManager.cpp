//
// Created by Qami on 11/23/2023.
//

#include "StateManager.h"
namespace Game {
void StateManager::pop() { stateManager.pop(); }

void StateManager::push(const states& s, const shared_ptr<StateManager>& StateManager) {
    stateManager.push(Game::StateFactory::stateFactory(s, StateManager));
}

State* StateManager::top() { return stateManager.top(); }

int StateManager::size() { return stateManager.size(); }

const shared_ptr<Logic::Score>& StateManager::getScore() const { return score; }

int& StateManager::getLevel() { return level; }

void StateManager::setLevel(int level) { StateManager::level = level; }

StateManager::StateManager() : score(make_shared<Logic::Score>()), camera(make_shared<Camera>()), level(0) {}

const shared_ptr<Camera>& StateManager::getCamera() const { return camera; }

void StateManager::resetStats() { score->resetStats(); }

void StateManager::incLevel() {
    cout << "Level up!" << endl;
    level++;
}
} // namespace Game