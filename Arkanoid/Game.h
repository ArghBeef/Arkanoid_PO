#pragma once

#include <SFML/Graphics.hpp>
#include "Ball.h"
#include "Player.h"
#include "Block.h"
#include <cstdlib>
#include <cstdio>

using namespace sf;
using namespace std;

class Game {
public:
    enum GameState { MENU = 1, GAMING, ENDSCREEN };
    bool TimerBool(Clock& clock, Text& text, float delay);
    void MenuLoad(RenderWindow& window, Text& infoText, int& currentScene, Clock& clock, vector<Ball>& balls, Vector2f mousePos);
    void GameLoadScenario(RenderWindow& window, Block& blocks, Player& plotinka, vector<Ball>& balls, Bonus& bonusik, Text& text, int& currentLevel, Clock& clock, bool& gameStarted, float delay, int& currentScene);
    void EndLoad(RenderWindow& window, Text& infoText, int& score, Vector2f mousePos);
};
