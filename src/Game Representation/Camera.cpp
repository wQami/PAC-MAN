//
// Created by Qami on 11/23/2023.
//

#include "Camera.h"
#include "../globalGame.h"
#include <iostream>

namespace Game {
sf::Vector2f Camera::calcScale(const int& mapH, const int& mapW, const int& size, const sf::RenderWindow& w) {
    float totalWidth = intToFloat(mapW * size);
    float totalHeight = intToFloat(mapH * size);

    scaleFactor = min(w.getSize().x / totalWidth, w.getSize().y / totalHeight);
    return {scaleFactor, scaleFactor};
}

Camera::Camera() : scaleFactor(0) {}
} // namespace Game