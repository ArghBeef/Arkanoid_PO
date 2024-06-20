
#include "Block.h"
#include "Bonus.h"
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <cstdio>

using namespace std;

Block::Block() {
    block_count = 0;
    currentlevel = 1;

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

void Block::LoadLevel(int level) {

    ifstream file("map/" + maps[level - 1]);
    if (!file) {
        printf("Failed to open level file");
        return;
    }

    string line;
    int j = 0;
    block_count = 0;
    scoremax = 0;

    while (getline(file, line) && j < 8) {
        for (int i = 0; i < line.length() && i < 13; i++) {
            char type = line[i];
            blocke[block_count].setSize(Vector2f(78.0f, 45.0f));
            blocke[block_count].setPosition(i * 79, j * 48);
            destroyed[block_count] = false;

            switch (type) {
            case '0':
                destroyed[block_count] = true;
                continue;
            case '1':
                blocke[block_count].setFillColor(Color::Red);
                scoremax++;
                break;
            case '2':
                blocke[block_count].setFillColor(Color::White);
                break;
            default:
                destroyed[block_count] = true; 
                continue;
            }

            block_count++;
        }
        j++;
    }
    scoremax = (scoremax / 4) * 3;
}


void Block::GenerateRandom() {
    int randomness = 0;
    scoremax = 0;
    for (int i = 0; i <= 12; i++) {
        for (int j = 0; j <= 7; j++) {
            blocke[block_count].setSize(Vector2f(75.0f, 44.0f));
            blocke[block_count].setPosition(i * 79, j * 48);
            destroyed[block_count] = false;
            randomness = rand() % 3;
            if(randomness == 2)
                blocke[block_count].setFillColor(Color::White);
            else {
                blocke[block_count].setFillColor(Color::Red);
                scoremax++;
            }
            block_count++;
        }
    }
}

void Block::CheckBlockCollision(Ball& ball, int& score, Bonus& bonus) {
    for (int i = 0; i < block_count; i++) {
        if (!isDestroyed(i) && FloatRect(ball.GetPosX() - ball.GetRadius(), ball.GetPosY() - ball.GetRadius(), ball.GetRadius() * 2, ball.GetRadius() * 2).intersects(getBounds(i))) {

            FloatRect blockBounds = getBounds(i);
            float overlapLeft = ball.GetPosX() + ball.GetRadius() - blockBounds.left;
            float overlapRight = blockBounds.left + blockBounds.width - (ball.GetPosX() - ball.GetRadius());
            float overlapTop = ball.GetPosY() + ball.GetRadius() - blockBounds.top;
            float overlapBottom = blockBounds.top + blockBounds.height - (ball.GetPosY() - ball.GetRadius());

            float minOverlap = min({ overlapLeft, overlapRight, overlapTop, overlapBottom });

            if (minOverlap == overlapLeft || minOverlap == overlapRight) {
                ball.SetVelocity(-ball.GetVelX(), ball.GetVelY());
            }
            else {
                ball.SetVelocity(ball.GetVelX(), -ball.GetVelY());
            }

            if (blocke[i].getFillColor() != Color::White) {
                int randomBonus = rand() % 2 + 1;
                bonus.Create(randomBonus, blocke[i].getPosition().x, blocke[i].getPosition().y);
                destroy(i);
                score++;
                scoremax--;
            }

            if (scoremax < 0 && currentlevel < LEVELS)
                currentlevel++;

            break;
        }
    }
}

void Block::DestroyLevel() {
    for (int i = 0; i < block_count; i++) {
        if (blocke[i].getFillColor() != Color::White) {
            destroy(i);
        }
    }
}
