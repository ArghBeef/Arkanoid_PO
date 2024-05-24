#include "Player.h"

Player::Player(float startX, float startY, float width, float height) {
    plotina.setSize(Vector2f(width, height));
    plotina.setFillColor(Color::Green);
    plotina.setPosition(startX, startY);
    plotina.setOrigin(startX + (startX/7), 0);
}

void Player::InputUpdate() {
    if (Mouse::isButtonPressed(Mouse::Left)) {
        Vector2i mousePos = Mouse::getPosition();
        plotina.setPosition(static_cast<float>(mousePos.x), plotina.getPosition().y);
    }
}


void Player::Draw(RenderWindow& window) {
    window.draw(plotina);
}

FloatRect Player::getBounds(){
    return plotina.getGlobalBounds();
}

void Player::CheckPlayerCollision(Ball& ball) {
    if (FloatRect(ball.GetPosX() - 25.0f, ball.GetPosY() - 25.0f, 25.0f * 2, 25.0f * 2).intersects(plotina.getGlobalBounds())) {
        ball.SetVelocity(ball.GetVelX(), -(static_cast<float>(rand()) / RAND_MAX * 0.4f + 0.1f));
    }
}
