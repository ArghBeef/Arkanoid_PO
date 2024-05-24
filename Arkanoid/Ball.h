#pragma once

#include <SFML/Graphics.hpp>
using namespace sf;

class Ball {
private:
	CircleShape ballie{};
	float radius;
	float dx, dy;
	float x, y;

public:
	Ball(float r, float xvel, float yvel, float startx, float starty);
	bool out = false;
	void Update();
	void SetVelocity(float xvel, float yvel);
	void Draw(RenderTarget& target);
	float GetPosX();
	float GetPosY();
	float GetVelX();
	float GetVelY();
	void SetVel(float xvel, float yvel);
};
