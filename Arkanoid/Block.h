#pragma once

#include <SFML/Graphics.hpp>
#include "Ball.h"
using namespace sf;

#define BLOCK_NUM 128

class Block {
private:
    int block_count;
    RectangleShape blocke[BLOCK_NUM];
    bool destroyed[BLOCK_NUM];

public:
    Block();
    FloatRect getBounds(int index);
    void Draw(RenderWindow& window);
    void destroy(int index);
    bool isDestroyed(int index);
    void Generate();
    void CheckBlockCollision(Ball& ball, int& score);
};