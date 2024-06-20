#include <SFML/Graphics.hpp>
#include <time.h>
#include <cstdlib>
#include <cstdio>
#include <vector>

#include "Ball.h"
#include "Player.h"
#include "Block.h"
#include "Bonus.h"
#include "Game.h"

using namespace sf;
using namespace std;

int main() {
    RenderWindow window(VideoMode(1025, 820), "ARKANOID");
    srand(time(0));
    window.setFramerateLimit(280);

    int currentLevel = 1;
    int currentScene = Game::MENU;
    Game game;

    Block blocks;
    blocks.LoadLevel(currentLevel);

    Player plotinka(450, 780, 120.0f, 25.0f);
    vector<Ball> balls;
    balls.push_back(Ball(25.0f, -1.5f, -1.5f, 510, 760));
    Bonus bonusik;

    Font font;
    Text text;
    Text infoText;
    if (!font.loadFromFile("tf2.ttf")) {
        printf("ERROR: Font file could not be loaded!");
        exit(1);
    }
    text.setFont(font);
    text.setCharacterSize(28);
    text.setPosition(0, 745);
    text.setFillColor(Color::White);

    infoText.setFont(font);
    infoText.setCharacterSize(24);
    infoText.setPosition(412, 200);
    infoText.setFillColor(Color::White);

    Clock clock;
    bool gameStarted = false;
    float delay = 3.0f;

    while (window.isOpen()) {
        Vector2f mousePos = window.mapPixelToCoords(Mouse::getPosition(window));

        Event evnt;
        while (window.pollEvent(evnt)) {
            if (evnt.type == Event::Closed)
                window.close();
            if (evnt.type == Event::KeyPressed && Keyboard::isKeyPressed(Keyboard::E)) {
                if (currentLevel != LEVELS)
                    blocks.LoadLevel(++currentLevel);
                else
                    currentLevel = 1;
            }
            if (evnt.type == Event::KeyPressed && Keyboard::isKeyPressed(Keyboard::R))
                blocks.scoremax--;
                //blocks.DestroyLevel();
        }

        window.clear();

        switch (currentScene)
        {
        case Game::MENU:
            game.MenuLoad(window, infoText, currentScene, clock, balls, mousePos);
            break;

        case Game::GAMING:
            game.GameLoadScenario(window, blocks, plotinka, balls, bonusik, text, currentLevel, clock, gameStarted, delay, currentScene);
            break;

        case Game::ENDSCREEN:
            game.EndLoad(window, infoText, plotinka.score, mousePos);
            break;
        }

        window.display();
    }

    return 0;
}
