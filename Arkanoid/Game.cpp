#include "Game.h"

//Похуй
bool Game::TimerBool(Clock& clock, Text& text, float delay) {
    float elapsed = clock.getElapsedTime().asSeconds();
    if (elapsed >= delay) {
        return true;
    } else {
        text.setString("Starting in: " + to_string(static_cast<int>(delay - elapsed)) + " seconds");
        return false;
    }
}

void Game::MenuLoad(RenderWindow& window, Text& infoText, int& currentScene, Clock& clock, vector<Ball>& balls, Vector2f mousePos) {
    infoText.setString("Click\nGreen to Play\nRed to Quit");

    RectangleShape startButton(Vector2f(200, 50));
    startButton.setPosition(412, 300);
    startButton.setFillColor(Color::Green);

    RectangleShape exitButton(Vector2f(200, 50));
    exitButton.setPosition(412, 385);
    exitButton.setFillColor(Color::Red);

    if (startButton.getGlobalBounds().contains(mousePos)) {
        startButton.setFillColor(Color::White);
        if (Mouse::isButtonPressed(Mouse::Left)) {
            currentScene = Game::GAMING;
            clock.restart();

            balls.clear();
            balls.push_back(Ball(25.0f, -1.5f, -1.5f, 510, 760));
        }
    } else {
        startButton.setFillColor(Color::Green);
    }

    // Check if the mouse is over the exit button
    if (exitButton.getGlobalBounds().contains(mousePos)) {
        exitButton.setFillColor(Color::White);
        if (Mouse::isButtonPressed(Mouse::Left)) {
            window.close();
        }
    } else {
        exitButton.setFillColor(Color::Red);
    }

    window.draw(startButton);
    window.draw(exitButton);
    window.draw(infoText);
}

void Game::GameLoadScenario(RenderWindow& window, Block& blocks, Player& plotinka, vector<Ball>& balls, Bonus& bonusik, Text& text, int& currentLevel, Clock& clock, bool& gameStarted, float delay, int& currentScene) {
    gameStarted = TimerBool(clock, text, delay);
    if (gameStarted) {
        plotinka.InputUpdate();
        for (int i = balls.size() - 1; i >= 0; --i) {
            balls[i].Update();
            plotinka.CheckPlayerCollision(balls[i]);
            blocks.CheckBlockCollision(balls[i], plotinka.score, bonusik);

            if (balls[i].out) {
                balls.erase(balls.begin() + i);
            }
        }

        bonusik.Update();
        bonusik.CheckCollision(plotinka, balls);

        text.setString("Score: " + to_string(plotinka.score));

        if (balls.empty()) {
            currentScene = Game::ENDSCREEN;
        }

        if (blocks.scoremax == 0) {
            blocks.LoadLevel(++currentLevel);
        }

        // Drawing logic
        blocks.Draw(window);
        plotinka.Draw(window);
        bonusik.Draw(window);
        for (auto& ball : balls) {
            ball.Draw(window);
        }
    }
    window.draw(text);
}

//ЕндЛоуд: Це якщо кінцевий екран, виставляється текст зі очками і якщо натиснута кнопка то вийти
void Game::EndLoad(RenderWindow& window, Text& infoText, int& score, Vector2f mousePos) {
    RectangleShape button(Vector2f(200, 50));
    button.setPosition(412, 400);
    button.setFillColor(Color::White);
    infoText.setString("Game Over! \nYour score: " + to_string(score));

    if (button.getGlobalBounds().contains(mousePos)) {
        button.setFillColor(Color::Red);
        if (Mouse::isButtonPressed(Mouse::Left)) {
            window.close();
        }
    } else {
        button.setFillColor(Color::White);
    }

    window.draw(button);
    window.draw(infoText);
}
