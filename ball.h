#pragma once
#include "GameRectangle.h"

class Ball : public GameRectangle {
public:
	Ball() = delete;
	Ball(Subject& subject, std::shared_ptr<SDL_Renderer*> render_ptr, int speed, int windowHeight, int windowWidth);

	void SetPosition() override;

	void IntersectionChangeDirection(SDL_Rect rectangle, size_t ifRight);
	int CheckPositionAndIntersection(SDL_Rect leftRectangle, SDL_Rect RightRectangle, int windowHeight, int windowWidth);

private:
	float velX = 0;
	float velY = 0;
};