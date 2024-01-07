//
// Created by Qami on 11/23/2023.
//

#ifndef PAC_MAN_CAMERA_H
#define PAC_MAN_CAMERA_H

#include "SFML/Graphics.hpp"

namespace Game {

class Camera {
private:
    float scaleFactor;

public:
    Camera();
    sf::Vector2f calcScale(const int& mapH, const int& mapW, const int& size, const sf::RenderWindow& w);
};

} // namespace Game

#endif // PAC_MAN_CAMERA_H
