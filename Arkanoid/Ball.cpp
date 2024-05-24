#include "Ball.h"


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

void Ball::Update() {

	if (x < 0 || x>995)  dx = -dx;
	if (y < 0)  dy = -dy;

	if (y > 795) out = true;

	x += dx;
	y += dy;

	ballie.setPosition(x, y);

}

void Ball::SetVelocity(float xvel, float yvel) {
	dx = xvel;
	dy = yvel;
}

void Ball::Draw(RenderTarget& target){
	target.draw(ballie);
}

float Ball::GetPosX() {
	return x;
}

float Ball::GetPosY() {
	return y;
}

float Ball::GetVelX() {
	return dx;
}

float Ball::GetVelY() {
	return dy;
}

void Ball::SetVel(float xvel, float yvel) {
	dx = xvel;
	dy = yvel;
} 

