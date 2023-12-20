//
// Created by Qami on 11/28/2023.
//

#ifndef PAC_MAN_SCORE_H
#define PAC_MAN_SCORE_H

#include <map>
#include <vector>
#include "Observer.h"
#include "Subject.h"
#include "EntityModel.h"

namespace Logic {

    class Score : public Observer {
    private:
        int score;
        int lives{};
        vector<int> highScores;
    public:
        Score();

        void update(EntityModel *subject) override;
        bool newHighScore(int s);
        void updateHighScores();
    };

} // Logic

#endif //PAC_MAN_SCORE_H
