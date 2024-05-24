#include <SFML/Graphics.hpp>
#include <time.h>
#include <cstdlib>
#include <cstdio>
#include "Ball.h"
#include "Player.h"
#include "Block.h" // Include the Block class header

using namespace sf;
using namespace std;

int main() {

    RenderWindow window(VideoMode(1020, 820), "ARKANOID");
    srand(time(0));

    int score = 0;

    Block blocks;
    blocks.Generate();

    Player plotinka(450, 780, 120.0f, 25.0f);
    Ball ball(25.0f, -0.1f, -0.1f, 510, 760);

    Font font;
    Text text;
    if (!font.loadFromFile("tf2.ttf"))
    {
        printf("ERROR");
        exit(0);
    }
    text.setFont(font);
    text.setCharacterSize(28);
    text.setPosition(0, 745);

    text.setFillColor(sf::Color::White);

    while (window.isOpen()) {
        Event evnt;
        while (window.pollEvent(evnt)) {
            if (evnt.type == Event::Closed)
                window.close();
        }

        plotinka.InputUpdate();
        ball.Update();
        plotinka.CheckPlayerCollision(ball);

        blocks.CheckBlockCollision(ball,score);
        text.setString("Score: " + to_string(score));

        if (ball.out) {
            window.close();
        }

        window.clear();
        blocks.Draw(window); // Draw all blocks using Block class method
        plotinka.Draw(window);
        ball.Draw(window);
        window.draw(text);
        window.display();
    }

    return 0;
}
