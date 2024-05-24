
#include "Block.h"

Block::Block() {
    block_count = 0;

}

FloatRect Block::getBounds(int index) {
    return blocke[index].getGlobalBounds();
}

void Block::Draw(RenderWindow& window) {
    for(int i = 0; i < block_count; i++)
    if (!destroyed[i]) {
        window.draw(blocke[i]);
    }
}

void Block::destroy(int index) {
    destroyed[index] = true;
}

bool Block::isDestroyed(int index) {
    return destroyed[index];
}

void Block::Generate() {
    int randomness = 0;
    for (int i = 0; i <= 12; i++) {
        for (int j = 0; j <= 7; j++) {
            blocke[block_count].setSize(Vector2f(78.0f, 45.0f));
            blocke[block_count].setPosition(i * 79, j * 48);
            destroyed[block_count] = false;
            randomness = rand() % 3;
            if(randomness == 2)
                blocke[block_count].setFillColor(Color::White);
            else
                blocke[block_count].setFillColor(Color::Red);
            block_count++;
        }
    }
}

void Block::CheckBlockCollision(Ball& ball, int& score) {
    for (int i = 0; i < BLOCK_NUM; i++) {
        if (!isDestroyed(i) && FloatRect(ball.GetPosX() - 25.0f, ball.GetPosY() - 25.0f, 25.0f * 2, 25.0f * 2).intersects(getBounds(i))) {

            ball.SetVelocity(ball.GetVelX(), -ball.GetVelY());
            if (blocke[i].getFillColor() == Color::White) {
                return;
            }
            destroy(i);
            score++;
            break;
        }
    }
}