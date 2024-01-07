//
// Created by Qami on 11/28/2023.
//

#ifndef PAC_MAN_SCORE_H
#define PAC_MAN_SCORE_H

#include "../globalGame.h"
#include "EntityModel.h"
#include "Observer.h"
#include "Subject.h"
#include <map>
#include <vector>

namespace Logic {

class Score : public Observer {
private:
    int score;
    int lives{};
    int interval;
    vector<int> highScores;

public:
    Score();

    [[nodiscard]] int getScore() const;
    [[nodiscard]] int getLives() const;
    [[nodiscard]] const vector<int>& getHighScores() const;

    void update(EntityModel* subject) override;

    bool newHighScore(int s);
    void updateHighScores();
    void printHighScores();
    void resetStats();
};

} // namespace Logic

#endif // PAC_MAN_SCORE_H
