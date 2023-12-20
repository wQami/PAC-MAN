//
// Created by Qami on 11/23/2023.
//

#include "Stopwatch.h"
#include <iostream>
#include <chrono>

namespace Logic {
    void Stopwatch::calcDeltaTime() {
        deltaTime = clock() - prevTime;
        //double fps = (1.0 / deltaTime) * 1000;
        prevTime = clock();
    }

    int Stopwatch::seconds(){
        return 0;
    }
} // Logic