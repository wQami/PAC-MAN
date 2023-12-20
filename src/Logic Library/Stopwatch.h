//
// Created by Qami on 11/23/2023.
//

#ifndef PAC_MAN_STOPWATCH_H
#define PAC_MAN_STOPWATCH_H

#include "ctime"

namespace Logic {

    class Stopwatch {
    private:
        double deltaTime = 0;
        double prevTime = 0;
        static Stopwatch* instance;
        Stopwatch() = default;
    public:
        ~Stopwatch() = default;

        void calcDeltaTime();
        int seconds();

        static Stopwatch* getInstance(){
            if(!instance)
                instance = new Stopwatch();
            return instance;
        };
    };

} // Logic

#endif //PAC_MAN_STOPWATCH_H
