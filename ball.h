#ifndef _BALL_
#define _BALL_

class Ball {
private:
	float directionX;
	float directionY;

public:
	float x;
	float y;
	float radius;

	Ball(float x, float y, float radius);
	void update(float delta_time);
};

#endif
