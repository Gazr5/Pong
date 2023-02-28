#pragma once
#include "GameRectangle.h"

class Player : public GameRectangle {
public:
	Player(Subject& subject, std::shared_ptr<SDL_Renderer*> render_ptr, int speed, int windowHeight, int windowWidth);

	bool PlayerMovement(const Uint8* keystates, const int& windowHeight);
};