//
// Created by Qami on 11/28/2023.
//

#include "MenuState.h"
#include "../StateManager.h"
#include <fstream>

namespace Game {
MenuState::MenuState(const shared_ptr<StateManager>& s) : State(s) {}

void MenuState::draw(RenderWindow& window) {
    Texture texture;
    Sprite sprite;
    Font font;
    Text start;
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

    start.setFont(font);
    start.setString("Press SPACE!");
    start.setOrigin(180.5, 15.5);
    start.setPosition(400, 500);
    start.setFillColor({255, 221, 0});

    string totalScores;
    vector<int> leaderBoard = getStateManager()->getScore()->getHighScores();
    for (int i = 0; i < leaderBoard.size(); i++)
        totalScores += to_string(i + 1) + ". " + to_string(leaderBoard[i]) + "\n";

    highscores.setFont(font);
    highscores.setString(totalScores);
    highscores.setOrigin(105.5, 75.5);
    highscores.setPosition(400, 325);

    highscoresHeader.setFont(font);
    highscoresHeader.setString("HIGHSCORES:");
    highscoresHeader.setOrigin(165.5, 15.5);
    highscoresHeader.setPosition(410, 210);

    window.clear();
    window.draw(sprite);
    window.draw(start);
    window.draw(highscores);
    window.draw(highscoresHeader);
    window.display();
}

MenuState::MenuState() : State() {}

void MenuState::keyPress() {
    if (Keyboard::isKeyPressed(Keyboard::Space) || Mouse::isButtonPressed(sf::Mouse::Left)) {
        getStateManager()->resetStats();
        getStateManager()->push(LEVEL, getStateManager());
    }
}

void MenuState::handlePeriod() {}
} // namespace Game