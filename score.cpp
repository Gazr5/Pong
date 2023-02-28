#include "score.h"

Score::Score(Subject& subject, std::shared_ptr<SDL_Renderer*> render_ptr, int windowHeight, int windowWidth) : GameObject(subject, render_ptr) {
	playerScore = 0;
	AIScore = 0;
	fontSize = 42;

	TTF_Init();
	Sans = TTF_OpenFont("ModernSansSerif7-m3Ym.ttf", fontSize);
	Color = { 255, 255, 255 };

	std::string text =  std::to_string(playerScore) + " : " + std::to_string(AIScore);

	SDL_Surface* surface;
	surface = TTF_RenderText_Solid(Sans, text.c_str(), Color);
	scoreBoard.w = surface->w;
	scoreBoard.h = surface->h;
	scoreBoard.x = windowWidth / 2 + fontSize - scoreBoard.w;
	scoreBoard.y = fontSize * 2 - scoreBoard.h;
}

void Score::AddPointToPlayer() {
	playerScore += 1;
}

void Score::AddPointToAI() {
	AIScore += 1;
}

void Score::Render() {
	std::string text = std::to_string(playerScore) + " : " + std::to_string(AIScore);

	SDL_Surface* surface;
	SDL_Texture* texture;
	const char* t = text.c_str();
	surface = TTF_RenderText_Solid(Sans, text.c_str(), Color);
	texture = SDL_CreateTextureFromSurface(*render_.get(), surface);
	scoreBoard.w = surface->w;
	scoreBoard.h = surface->h;
	scoreBoard.x = 1200 / 2 + fontSize - scoreBoard.w;
	scoreBoard.y = fontSize * 2 - scoreBoard.h;
	SDL_FreeSurface(surface);
	SDL_RenderCopy(*render_.get(), texture, NULL, &scoreBoard);
	SDL_DestroyTexture(texture);
}

void Score::Update(const std::string& message_from_subject) {
	if (message_from_subject == "Render") {
		Render();
	}
}