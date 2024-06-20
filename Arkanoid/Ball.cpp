#include "Ball.h"

//Конструктор до мяча, де радіус, швидкість ікс і ігрік, початкова ікс ігрік
Ball::Ball(float r, float xvel, float yvel, float startx, float starty) {
    radius = r;
    dx = xvel;
    dy = yvel;
    ballie = CircleShape(radius);
    x = startx;
    y = starty;
    ballie.setPosition(x, y);
    ballie.setFillColor(Color::Blue);
    ballie.setOrigin(radius - (radius / 2), radius - (radius / 2));
}

//Обновленя мяча. Якщо там менше 0 і більше тисячі то це рамки екрану
//І воно ставиться на мінус - тобто в протилежну сторону відбивається
void Ball::Update() {
    if (x < 0 || x > 1000) dx = -dx;
    if (y < 0) dy = -dy;

    if (y > 795) {
        out = true; //Якщо вилітає то тру
    }

    //Це зміна швидкості: Додаються координати до швидкості
    x += dx;
    y += dy;
    ballie.setPosition(x, y);
}

//Виставити швидкість
void Ball::SetVelocity(float xvel, float yvel) {
    dx = xvel;
    dy = yvel;
}

//Малювати мяч
void Ball::Draw(RenderTarget& target) {
    target.draw(ballie);
}

//Взнати ікс ігрік
float Ball::GetPosX() {
    return x;
}

float Ball::GetPosY() {
    return y;
}

//Дізнатись швидкість ікс і ігрік
float Ball::GetVelX() {
    return dx;
}

float Ball::GetVelY() {
    return dy;
}

//Теж але радіус
float Ball::GetRadius() {
    return radius;
}
