#include "player.h"

Player::Player(Subject& subject, std::shared_ptr<SDL_Renderer*> render_ptr, int speed, int windowHeight, int windowWidth) : GameRectangle(subject, render_ptr, speed, windowHeight, windowWidth) {
	startXPosition = 0;
	startYPosition = static_cast<int>(windowHeight / 2 - rectangle.h / 2);

	rectangle.x = startXPosition;
	rectangle.y = startYPosition;
}

bool Player::PlayerMovement(const Uint8* keystates, const int& windowHeight) {
	if (keystates[SDL_SCANCODE_UP] && rectangle.y > 0) rectangle.y -= getSpeed();
	if (keystates[SDL_SCANCODE_DOWN] && rectangle.y < windowHeight - rectangle.h) rectangle.y += getSpeed();

	return true;
}