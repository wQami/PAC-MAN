//
// Created by Qami on 11/28/2023.
//

#include "GameOverState.h"

namespace Game {
GameOverState::GameOverState(const shared_ptr<StateManager>& context) : State(context) {}

void GameOverState::draw(RenderWindow& window) {
    Texture texture;
    Sprite sprite;
    Font font;
    Text resume;
    Text end;
    Text highscores;
    Text highscoresHeader;
    try {
        font.loadFromFile(PATH_FONTS + FONT_MASTER);
        texture.loadFromFile(PATH_IMAGES + IMAGE_PACMAN_LOGO);
        texture.setSmooth(true);
        sprite.setTexture(texture);
        sprite.setOrigin(279, 73.5);
        sprite.setPosition(400, 100);
    } catch (string& err) {
        cout << "Error:" << err << endl;
    }

    resume.setFont(font);
    resume.setString("Press SPACE to play again!");
    resume.setOrigin(390.5, 15.5);
    resume.setPosition(400, 530);
    resume.setFillColor({255, 221, 0});

    end.setFont(font);
    end.setString("Press X to go to menu!");
    end.setOrigin(330.5, 15.5);
    end.setPosition(400, 495);
    end.setFillColor({255, 0, 0});

    string totalScores;
    vector<int> leaderBoard = getStateManager()->getScore()->getHighScores();
    for (int i = 0; i < leaderBoard.size(); i++)
        totalScores += to_string(i + 1) + ". " + to_string(leaderBoard[i]) + "\n";

    highscores.setFont(font);
    highscores.setString(totalScores);
    highscores.setOrigin(105.5, 75.5);
    highscores.setPosition(400, 325);

    highscoresHeader.setFont(font);
    highscoresHeader.setString("GAME OVER!");
    highscoresHeader.setOrigin(150.5, 15.5);
    highscoresHeader.setPosition(410, 210);

    window.clear();
    window.draw(sprite);
    window.draw(end);
    window.draw(resume);
    window.draw(highscores);
    window.draw(highscoresHeader);
    window.display();
}

void GameOverState::keyPress() {
    if (Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        getStateManager()->resetStats();
        getStateManager()->push(LEVEL, getStateManager());
    }

    if (Keyboard::isKeyPressed(sf::Keyboard::X)) {
        while (getStateManager()->size() != 1) {
            getStateManager()->pop();
        }
    }
}

void GameOverState::handlePeriod() {}
} // namespace Game