//
// Created by Qami on 11/20/2023.
//

#include "Game.h"
#include "States/MenuState.h"
#include <iostream>

Game::Game::Game()
    : window(RenderWindow{{SCREEN_WIDTH, SCREEN_HEIGHT}, "PAC-MAN"}), stateManager(make_shared<StateManager>()) {
    window.setFramerateLimit(144);
    Image icon;
    icon.loadFromFile(PATH_IMAGES + "Icon.png");
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    stateManager->push(MENU, stateManager);
    stateManager->top()->draw(window);
}

void Game::Game::run() {
    sf::FloatRect view;
    int currentSize = stateManager->size();

    while (window.isOpen()) {
        Logic::Stopwatch::getInstance()->newDeltaTime();
        handleStackChange(currentSize);
        drawLevel();
        stateManager->top()->handlePeriod();

        for (auto event = Event{}; window.pollEvent(event);) {
            switch (event.type) {
            // window closed
            case sf::Event::Closed:
                window.close();
                break;

                // key pressed
            case sf::Event::KeyPressed:
                stateManager->top()->keyPress();
                break;

            case sf::Event::MouseButtonPressed:
                stateManager->top()->keyPress();
                break;

            case sf::Event::Resized:
                view = FloatRect(0, 0, event.size.width, event.size.height);
                window.setView(sf::View(view));
                break;

                // we don't process other types of events
            default:
                break;
            }
        }
    }
}

void Game::Game::handleStackChange(int& currentSize) {
    if (stateManager->size() != currentSize) {
        currentSize = stateManager->size();
        stateManager->top()->draw(window);
        Logic::Stopwatch::getInstance()->newDeltaTime();
    }
}

void Game::Game::drawLevel() {
    if (stateManager->size() % 2 == 0) {
        stateManager->top()->draw(window);
        Logic::Stopwatch::getInstance()->newDeltaTime();
    }
}
