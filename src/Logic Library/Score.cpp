//
// Created by Qami on 11/28/2023.
//

#include "Score.h"
#include "EntityModel.h"
#include "FileReader.h"
#include "FileWriter.h"
#include "Stopwatch.h"
#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>

namespace Logic {
Score::Score() : lives(3), interval(0), score(0) {
    FileReader fileReader(HIGHSCORE_MASTER);
    fileReader.scoreReader(highScores);
    std::sort(highScores.begin(), highScores.end(), greater<>());
    printHighScores();
}

void Score::update(EntityModel* subject) {
    int roundedToNearestFive;
    auto sw = Stopwatch::getInstance();
    switch (subject->getType()) {
    case PACMAN:
        if (lives > 0)
            lives -= subject->getValue();
        if (lives == 0)
            subject->setType(LOSER_PACMAN);
        cout << "Lives: " << lives << endl;
        break;

    case LOSER_PACMAN:
        score -= 500;
    case WINNER_PACMAN:
        score += 500;
        if (newHighScore(score)) {
            updateHighScores();
            cout << "NEW HIGHSCORE!" << endl;
        }

        cout << "Score: " << score << endl;
        if (lives != 0)
            cout << "Lives: " << lives << endl;
        break;

    case COIN:
        roundedToNearestFive = roundToNearestInt(subject->getValue() / sw->timeSinceLastCoin(), 5);
        score += max(roundedToNearestFive, 10);
        cout << "Score: " << score << endl;
        sw->resetCoin();
        break;

    case GHOST:
    case SCATTER_GHOST:
    case FRIGHTENED_GHOST:
        break;

    default:
        score += subject->getValue();
        cout << "Score: " << score << endl;
        break;
    }

    if (sw->totalPassed(DECREMENT_SPEED, interval)) {
        if (score > 0)
            score -= 5;
    }
}

bool Score::newHighScore(int s) {
    if (highScores.empty()) {
        highScores.push_back(s);
        return true;
    } else {
        for (int i = 0; i < 5; i++) {
            if (highScores[i] == s) {
                if (highScores.size() > 5)
                    highScores.pop_back();
                return false;
            }

            if (highScores[i] < s) {
                highScores.insert(highScores.begin() + i, s);
                if (highScores.size() > 5)
                    highScores.pop_back();
                return true;
            }
        }
        if (highScores.size() < 5) {
            highScores.push_back(s);
        }
    }
    if (highScores.size() > 5)
        highScores.pop_back();
    return false;
}

void Score::updateHighScores() {
    FileWriter fileWriter(PATH_HIGHSCORES + HIGHSCORE_MASTER);
    fileWriter.scoreWriter(highScores);
}

void Score::printHighScores() { FileWriter::scoreOut(highScores); }

int Score::getScore() const { return score; }

int Score::getLives() const { return lives; }

void Score::resetStats() {
    score = 0;
    lives = 3;
}

const vector<int>& Score::getHighScores() const { return highScores; }
} // namespace Logic