#include "AI.h"

AI::AI(Subject& subject, std::shared_ptr<SDL_Renderer*> render_ptr, int speed, int windowHeight, int windowWidth) : GameRectangle(subject, render_ptr, speed, windowHeight, windowWidth) {
	startXPosition = windowWidth - rectangle.w;
	startYPosition = static_cast<int>(windowHeight / 2 - rectangle.h / 2);

	rectangle.x = startXPosition;
	rectangle.y = startYPosition;
}

void AI::Move(const int& YBall, const int& windowHeight) {
	if (YBall > rectangle.y + (rectangle.h / 2) && rectangle.y < windowHeight - rectangle.h)
		rectangle.y += speed;
	if (YBall < rectangle.y + (rectangle.h / 2) && rectangle.y > 0)
		rectangle.y -= speed;
}