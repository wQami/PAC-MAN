//
// Created by Qami on 11/28/2023.
//

#include "PausedState.h"

namespace Game {
PausedState::PausedState(const shared_ptr<StateManager>& context) : State(context) {}

void PausedState::draw(RenderWindow& window) {
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
    resume.setString("Press SPACE to resume!");
    resume.setOrigin(330.5, 15.5);
    resume.setPosition(400, 530);
    resume.setFillColor({255, 221, 0});

    end.setFont(font);
    end.setString("Press X to give up!");
    end.setOrigin(285.5, 15.5);
    end.setPosition(400, 495);
    end.setFillColor({255, 0, 0});

    ifstream highscore;
    highscore.open(PATH_HIGHSCORES + HIGHSCORE_MASTER);

    string scores;
    string totalScores;
    while (getline(highscore, scores)) {
        totalScores += scores + "\n";
    }

    highscores.setFont(font);
    highscores.setString(totalScores);
    highscores.setOrigin(105.5, 75.5);
    highscores.setPosition(400, 295);

    highscoresHeader.setFont(font);
    highscoresHeader.setString("GAME PAUSED!");
    highscoresHeader.setOrigin(180.5, 15.5);
    highscoresHeader.setPosition(410, 180);

    window.clear();
    window.draw(sprite);
    window.draw(end);
    window.draw(resume);
    window.draw(highscores);
    window.draw(highscoresHeader);
    window.display();
}

void PausedState::keyPress() {
    if (Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        getStateManager()->pop();
    }

    if (Keyboard::isKeyPressed(sf::Keyboard::X)) {
        while (getStateManager()->size() != 1) {
            getStateManager()->pop();
        }
    }
}

void PausedState::handlePeriod() {}
} // namespace Game