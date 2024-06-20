#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <cstdlib>
#include "Player.h"
#include "Ball.h"
using namespace sf;
using namespace std;

#define BONUS_NUM 8

class Bonus {
private:
    RectangleShape bonusik[BONUS_NUM];
    bool isDropped[BONUS_NUM];
    float speed = 1.2f;
public:
    Bonus();
    void Create(int type, float x, float y);
    void Draw(RenderWindow& window);
    void Update();
    void CheckCollision(Player& player, vector<Ball>& balls);
};