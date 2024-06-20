#pragma once

#include <SFML/Graphics.hpp>
#include "Ball.h"
using namespace sf;

class Player {
private:
    RectangleShape plotina;
    float speed;

public:
    int score = 0;
    Player(float startX, float startY, float width, float height);

    void InputUpdate();
    float GetPosX();
    float GetPosY();
    //void update();
    void Draw(RenderWindow& window);
    FloatRect getBounds();
    void CheckPlayerCollision(Ball& ball);
};
