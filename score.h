#pragma once
#include <SDL_ttf.h>
#undef main
#include "GameObject.h"

class Score : public GameObject {
public:
	Score() = delete;
	Score(Subject& subject, std::shared_ptr<SDL_Renderer*> render_ptr, int windowHeight, int windowWidth);

	void AddPointToPlayer();
	void AddPointToAI();
	void Render();

	void Update(const std::string& message_from_subject);

private:
	int playerScore = 0;
	int AIScore = 0;

	int fontSize = 0;

	TTF_Font* Sans;
	SDL_Rect scoreBoard;
	SDL_Color Color;
};