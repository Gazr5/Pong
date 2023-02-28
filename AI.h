#pragma once
#include "GameRectangle.h"

class AI : public GameRectangle {
public:
	AI() = delete;
	AI(Subject& subject, std::shared_ptr<SDL_Renderer*> render_ptr, int speed, int windowHeight, int windowWidth);

	void Move(const int& YBall, const int& windowHeight);
};