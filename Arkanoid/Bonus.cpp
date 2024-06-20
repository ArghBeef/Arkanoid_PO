    #include "Bonus.h"


//Конструктор до Бонусів. Воно на початку кожен бонус виставляє "дроппед" на фолс і задає всім розмір
    Bonus::Bonus() {
        for (int i = 0; i < BONUS_NUM; i++) {
            isDropped[i] = false;
            bonusik[i].setSize(Vector2f(30.0f, 30.0f));
        }
    }

    //Створює бонус
    void Bonus::Create(int type, float x, float y) {
        if (rand() % 100 < 15) { //Це рандом (15 відсотків що зявиться бонус)
            for (int i = 0; i < BONUS_NUM; i++) {
                if (!isDropped[i]) {
                    bonusik[i].setPosition(x, y);
                    isDropped[i] = true;
                    switch (type) { //Це переглядає типи, є червоний і зелений
                    case 1:
                        bonusik[i].setFillColor(Color::Red);
                        break;
                    case 2:
                        bonusik[i].setFillColor(Color::Green);
                        break;
                    }
                    break;
                }
            }
        }
    }

    //Малює кожен якщо дроппед
    void Bonus::Draw(RenderWindow& window) {
        for (int i = 0; i < BONUS_NUM; i++)
            if (isDropped[i]) {
                window.draw(bonusik[i]);
            }
    }

    //З кожним оновленням, змінює позицію +швидкість і якщо виходить за рамки то дроппед на фолс і не показується
    void Bonus::Update() {
        for (int i = 0; i < BONUS_NUM; i++) {
            if (isDropped[i]) {
                Vector2f position = bonusik[i].getPosition();
                position.y += speed;
                bonusik[i].setPosition(position);

                if (position.y > 795)
                    isDropped[i] = false;
            }
        }
    }

    //провіряє колізію з плотінкою
    void Bonus::CheckCollision(Player& player, vector<Ball>& ball) {
        for (int i = 0; i < BONUS_NUM; i++) {
            if (isDropped[i] && bonusik[i].getGlobalBounds().intersects(player.getBounds())) {
                if (bonusik[i].getFillColor() == Color::Red) { //Якщо колір червоний, то множить рахунок на 1.25
                    player.score *= 1.25;
                }
                else if (bonusik[i].getFillColor() == Color::Green) { //Якщо зелений, то виставляє новий мяч
                    float randomX = (static_cast<float>(rand()) / RAND_MAX * 3.0f - 1.5f) * (1.5f + 1.0f);
                    ball.push_back(Ball(25.0f, randomX, -1.5f, 450, 780));
                }

                isDropped[i] = false;
            }
        }
    }







