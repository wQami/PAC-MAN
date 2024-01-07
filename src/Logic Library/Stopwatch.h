//
// Created by Qami on 11/23/2023.
//

#ifndef PAC_MAN_STOPWATCH_H
#define PAC_MAN_STOPWATCH_H

#include <chrono>
#include <ctime>
#include <memory>

using namespace std;
using namespace std::chrono;

namespace Logic {

class Stopwatch {
private:
    time_point<high_resolution_clock> prevTime;
    time_point<high_resolution_clock> prevprevTime;
    chrono::seconds startSecond;
    chrono::seconds frightSecond;
    chrono::milliseconds lastCoinSecond;
    chrono::milliseconds zeroSecond;
    inline static shared_ptr<Stopwatch> m_instance;

    bool frightAlmostDue;
    Stopwatch();

public:
    ~Stopwatch() = default;

    [[nodiscard]] bool isFrightAlmostDue() const;

    void reset();
    void resetCoin();
    void resetFright();
    void newDeltaTime();
    float calcDeltaTime();
    int calcFrames();
    double timeSinceLastCoin();
    void frightLeft(const int& s);
    bool secondsPassed(const int& s);
    bool totalPassed(const double& ms, int&);

    static shared_ptr<Stopwatch> getInstance();
};

} // namespace Logic

#endif // PAC_MAN_STOPWATCH_H
