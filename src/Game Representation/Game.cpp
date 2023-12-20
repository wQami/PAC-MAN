//
// Created by Qami on 11/20/2023.
//

#include "Game.h"
#include <iostream>

void Game::Game::run() {

    stateManager = StateManager();
    cout << stateManager.top() << endl;
//    string pathImages = "resources/images/";
//    string image_SpriteTextures = "Sprites.png";
//    int blankPixels = 15;
//    int heightSprite, widthSprite;
//    heightSprite = widthSprite = 35;
//
//
//    auto window = RenderWindow{ { 800u, 600u }, "PAC-MAN" };
//    window.setFramerateLimit(144);
//    Texture texture;
//
//    if(!texture.loadFromFile(pathImages + image_SpriteTextures)){
//        cout << "Sprite image not found." << endl;
//    }
//
//    Sprite sprite;
//    sprite.setTexture(texture);
//    IntRect originRect(1,4,35,35);
//    sprite.setTextureRect(originRect);

//    while (window.isOpen())
//    {
//        for (auto event = Event{}; window.pollEvent(event);)
//        {
//            if (event.type == Event::Closed)
//            {
//                window.close();
//            }
//        }
//
//        if (Keyboard::isKeyPressed(Keyboard::D)) {
//            sprite.move(5, 0);
//            int xTexture = (int) sprite.getPosition().x / 10 % 2;
//            IntRect rect = originRect;
//            rect.top += (blankPixels + heightSprite) * xTexture;
//            sprite.setTextureRect(rect);
//        }
//
//        if (Keyboard::isKeyPressed(Keyboard::A)) {
//            sprite.move(-5, 0);
//            int xTexture = (int) sprite.getPosition().x / 10 % 2;
//            IntRect rect = originRect;
//            rect.top += (blankPixels + heightSprite) * xTexture;
//            sprite.setTextureRect(rect);
//        }
//
//        window.clear();
//        window.draw(sprite);
//        window.display();
//    }
}
