#pragma once

#include <SFML/Graphics.hpp>
#include "Ball.h"
#include "Bonus.h"
#include <string>
using namespace sf;
using namespace std;

#define BLOCK_NUM 128
#define LEVELS 8

class Block {
private:
    int block_count;
    RectangleShape blocke[BLOCK_NUM];
    bool destroyed[BLOCK_NUM];
    string maps[LEVELS] = {"map01.txt","map02.txt", "map03.txt", "map04.txt", "map05.txt", "map06.txt", "map07.txt", "map08.txt" };

public:
    int currentlevel;
    int scoremax;
    Block();
    FloatRect getBounds(int index);
    void Draw(RenderWindow& window);
    void destroy(int index);
    bool isDestroyed(int index);
    void GenerateRandom();
    void CheckBlockCollision(Ball& ball, int& score, Bonus& bonus);
    void LoadLevel(int level);
    void DestroyLevel();
};