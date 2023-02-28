#pragma once
#include "player.h"
#include "AI.h"
#include "ball.h"
#include "score.h"

#define WINDOWHEIGHT 1000
#define WINDOWWIDTH  1200
#define BALLSPEED    16
#define PADDLESPEED  8

class Game : public Subject{
public:
	Game();

	void PlayingGame();
	void NewRound();
	void Update();
	void CheckPlayerControl();
	void Render();
	void EndGame();

private:
	SDL_Renderer* renderer; 
	std::shared_ptr<SDL_Renderer*> render_;
	SDL_Window* window;
	SDL_Color color;
	bool isRunning;

	int frameCount;
	int timerFPS;
	int lastFrame;
	int fps;

	std::unique_ptr<Player> player;
	std::unique_ptr<AI> ai;
	std::unique_ptr<Ball> ball;
	std::unique_ptr<Score> score;
};