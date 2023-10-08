#include "ball.h"
#include "constants.h"


Ball::Ball(float x, float y, float radius) {
	this->x = x;
	this->y = y;
	this->radius = radius;
	this->directionX = 1;
	this->directionY = 1;
};

void Ball::update(float delta_time) {
	if (this->x > (SCREEN_WIDTH - this->radius) || this->x < 0) {
		this->directionX *= -1;
	}

	if (this->y > (SCREEN_HEIGHT - this->radius) || this->y < 0) {
		this->directionY *= -1;
	}

	this->x += this->directionX * 80 * delta_time;
	this->y += this->directionY * 120 * delta_time;
}