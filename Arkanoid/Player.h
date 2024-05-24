#pragma once

#include <SFML/Graphics.hpp>
#include "Ball.h"
using namespace sf;

class Player {
private:
    RectangleShape plotina;
    float speed;

public:
    Player(float startX, float startY, float width, float height);

    void InputUpdate();
    //void update();
    void Draw(RenderWindow& window);
    FloatRect getBounds();
    void CheckPlayerCollision(Ball& ball);
};
