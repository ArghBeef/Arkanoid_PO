#include "Player.h"

//Це конструктор, подається початкове ікс ігрік ширина і висота і це все виставляється (і білий колір)
Player::Player(float startX, float startY, float width, float height) {
    plotina.setSize(Vector2f(width, height));
    plotina.setFillColor(Color::White);
    plotina.setPosition(startX, startY);
    plotina.setOrigin(startX + (startX/7), 0);
}

//Отримати позицію X
float Player::GetPosX() {
    return plotina.getPosition().x;
}

//Отримати позицію Y
float Player::GetPosY() {
    return plotina.getPosition().y;
}

//Отримати позицію межі обєкту
FloatRect Player::getBounds() {
    return plotina.getGlobalBounds();
}

//Провірка, чи натиснута ліва клавіша і миші і якщо так, то рухати гравця по іксу де миш
void Player::InputUpdate() {
    if (Mouse::isButtonPressed(Mouse::Left)) {
        Vector2i mousePos = Mouse::getPosition();
        plotina.setPosition(static_cast<float>(mousePos.x), plotina.getPosition().y);
    }
}


//Малювати плотину
void Player::Draw(RenderWindow& window) {
    window.draw(plotina);
}

//Провірити чи вона бється об мяч. Якщо (іф) мяч перетинає платформу, то виставити швидкість мяча: Ікс залишається а Ігрік відємне рандомне
//похуй закинь в гпт і хай розкаже як це ну запутано похуй
void Player::CheckPlayerCollision(Ball& ball) {
    if (FloatRect(ball.GetPosX() - 25.0f, ball.GetPosY() - 25.0f, 25.0f * 2, 25.0f * 2).intersects(plotina.getGlobalBounds())) {
        ball.SetVelocity(ball.GetVelX(), -(static_cast<float>(rand()) / RAND_MAX * 1.5f + 1.0f));
    }
}
