#include "ball.h"
#include <time.h>
#include <cstdlib>

#define PI 3.14159265358979323846

Ball::Ball(Subject& subject, std::shared_ptr<SDL_Renderer*> render_ptr, int speed, int windowHeight, int windowWidth) : GameRectangle(subject, render_ptr, speed, windowHeight, windowWidth) {
	srand(0);

	rectangle.w = rectangle.h = 16;
	startXPosition = static_cast<int>(windowWidth / 2);
	startYPosition = static_cast<int>(windowHeight / 2);
	SetPosition();

	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
}

void Ball::SetPosition() {
	GameRectangle::SetPosition();
	velX = (rand() % 2 == 1 ? -1 : 1) * speed;
	velY = 0;
}

void Ball::IntersectionChangeDirection(SDL_Rect intersection, size_t ifRight) {
	const double rel = (intersection.y + (intersection.h / 2)) - (this->rectangle.y + (this->rectangle.h / 2));
	const double norm = rel / (intersection.h / 2);
	const double bounce = norm * (5 * PI / 12);
	velX = (ifRight == 1 ? -1 : 1) * speed * cos(bounce);
	velY = speed * -sin(bounce);

	Mix_PlayChannel(-1, Mix_LoadWAV("hit.wav"), 0);
}

int Ball::CheckPositionAndIntersection(SDL_Rect leftRectangle, SDL_Rect rightRectangle, int windowHeight, int windowWidth) {
	int return_value = -1;

	if (SDL_HasIntersection(&rectangle, &leftRectangle))
		IntersectionChangeDirection(leftRectangle, 0);
	else if (SDL_HasIntersection(&rectangle, &rightRectangle))
		IntersectionChangeDirection(rightRectangle, 1);

	if (rectangle.x + rectangle.w >= windowWidth)
		return_value = 0;
	else if (rectangle.x <= 0)
		return_value = 1;

	if (rectangle.y <= 0 || rectangle.y + rectangle.h >= windowHeight) velY = -velY;

	rectangle.x += velX;
	rectangle.y += velY;

	return return_value;
}