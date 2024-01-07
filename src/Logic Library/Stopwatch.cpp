//
// Created by Qami on 11/23/2023.
//

#include "Stopwatch.h"
#include <cmath>
#include <iostream>
namespace Logic {
Stopwatch::Stopwatch()
    : frightAlmostDue(false), prevprevTime(high_resolution_clock::now()), prevTime(high_resolution_clock::now()),
      zeroSecond(milliseconds(duration_cast<milliseconds>(steady_clock::now().time_since_epoch()))),
      startSecond(seconds(duration_cast<seconds>(steady_clock::now().time_since_epoch()))) {
    lastCoinSecond = zeroSecond;
    frightSecond = startSecond;
}

shared_ptr<Stopwatch> Stopwatch::getInstance() {
    if (!m_instance)
        m_instance = make_shared<Stopwatch>(Stopwatch());
    return m_instance;
}

void Stopwatch::reset() { startSecond = seconds(duration_cast<seconds>(steady_clock::now().time_since_epoch())); }

void Stopwatch::resetCoin() {
    lastCoinSecond = milliseconds(duration_cast<milliseconds>(steady_clock::now().time_since_epoch()));
}

void Stopwatch::resetFright() {
    frightSecond = seconds(duration_cast<seconds>(steady_clock::now().time_since_epoch()));
    frightAlmostDue = false;
}

void Stopwatch::newDeltaTime() {
    time_point<high_resolution_clock> clockNow = high_resolution_clock::now();
    prevprevTime = prevTime;
    prevTime = clockNow;
}

float Stopwatch::calcDeltaTime() {
    auto deltaTime = prevTime - prevprevTime;
    return duration<float>(duration_cast<milliseconds>(deltaTime)).count();
}

int Stopwatch::calcFrames() { return lround(1 / calcDeltaTime()); }

bool Stopwatch::secondsPassed(const int& s) {
    duration<long long> timeInSeconds = duration<long long>(0);

    timeInSeconds = seconds(duration_cast<seconds>(steady_clock::now().time_since_epoch())) - startSecond;

    if (timeInSeconds >= seconds(s)) {
        return true;
    }
    return false;
}

double Stopwatch::timeSinceLastCoin() {
    auto timeInSeconds =
        milliseconds(duration_cast<milliseconds>(steady_clock::now().time_since_epoch())) - lastCoinSecond;
    return max(duration<double>(timeInSeconds).count(), 0.0001);
}

bool Stopwatch::totalPassed(const double& ms, int& lastInterval) {
    auto timeInMilliseconds =
        milliseconds(duration_cast<milliseconds>(steady_clock::now().time_since_epoch())) - zeroSecond;

    int msCount = ::floor(duration<double>(timeInMilliseconds / ms).count() * 1000);
    if (msCount > lastInterval) {
        lastInterval = msCount;
        return true;
    }
    return false;
}

void Stopwatch::frightLeft(const int& s) {
    auto timeElapsed = seconds(duration_cast<seconds>(steady_clock::now().time_since_epoch())) - frightSecond;
    auto timeLeft = seconds(s) - timeElapsed;
    frightAlmostDue = (timeLeft <= seconds(2));
}

bool Stopwatch::isFrightAlmostDue() const { return frightAlmostDue; }
} // namespace Logic