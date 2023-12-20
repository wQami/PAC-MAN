//
// Created by Qami on 11/28/2023.
//

#include <iostream>
#include <fstream>
#include "Score.h"
#include "EntityModel.h"

namespace Logic {
    void Score::update(EntityModel *subject) {
        switch(subject->getType()){
            case PACMAN:
                lives = subject->getValue();
                cout << "Lives: " << lives << endl;
                break;

            case LOSER_PACMAN:
            case WINNER_PACMAN:
                if (newHighScore(score)) {
                    cout << "NEW HIGHSCORE!" << endl;
                }

                cout << "Score: " << score << endl;
                if(lives != 0) cout << "Lives: " << lives << endl;
                break;

            default:
                score += subject->getValue();
                cout << "Score: " << score << endl;
                break;
        }
    }

    Score::Score() {
        score = 0;
        string highScore;
        ifstream  file("resources/highscores/highscores.txt");
        if(file.is_open()){
            while (getline (file, highScore)) {
                highScores.push_back(stoi(highScore));
            }
            file.close();
        }
    }

    bool Score::newHighScore(int s) {
        if(highScores.empty()){
            highScores.push_back(s);
            updateHighScores();
            return true;
        } else {
            for(int i = 0; i < 5; i++){
                if(highScores[i] == s){
                    return false;
                }

                if(highScores[i] < s){
                    highScores.insert(highScores.begin()+i, s);
                    updateHighScores();
                    return true;
                }
            }
            if(highScores.size() < 5){
                highScores.push_back(s);
                updateHighScores();
            }
        }
        return false;
    }

    void Score::updateHighScores() {
        ofstream file("resources/highscores/highscores.txt");
        for(auto h : highScores){
            file << h << endl;
        }
        file.close();
    }
} // Logic