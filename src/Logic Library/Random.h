//
// Created by Qami on 11/23/2023.
//

#ifndef PAC_MAN_RANDOM_H
#define PAC_MAN_RANDOM_H
#include <memory>
#include <random>

using namespace std;

namespace Logic {

class Random {
private:
    std::random_device rd;
    mt19937 MesserneTwister{rd()};
    static Random* m_instance;
    Random() = default;

public:
    ~Random() = default;
    int receiveRandom(int x, int y);

    static Random* getInstance();
};

} // namespace Logic

#endif // PAC_MAN_RANDOM_H
