//
// Created by Qami on 11/23/2023.
//

#include "Random.h"

namespace Logic {
    int Random::receiveRandom(int x , int y) {
        static std::uniform_int_distribution<int> uid(x,y);
        return uid(MesserneTwister);
    }

    Random* Random::m_instance;
    Random* Random::getInstance() {
        if(!m_instance) m_instance = new Random();
        return m_instance;
    }

} // Logic