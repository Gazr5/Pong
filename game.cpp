#include "game.h"

Game::Game(){
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
		std::cout << "Failed at SDL_Init()" << std::endl;
	if (SDL_CreateWindowAndRenderer(WINDOWWIDTH, WINDOWHEIGHT, 0, &window, &renderer) < 0)
		std::cout << "Failed at SDL_CreateWindowAndRenderer())" << std::endl;

	isRunning = false;

	frameCount = 0;
	timerFPS = 0;
	lastFrame = 0;
	fps = 0;

	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
	Mix_PlayMusic(Mix_LoadMUS("music.mp3"), -1);
	
	render_ = std::make_shared<SDL_Renderer*>(renderer);
	player = std::unique_ptr<Player>(new Player(*this, render_, PADDLESPEED, WINDOWHEIGHT, WINDOWWIDTH));
	ai = std::unique_ptr<AI>(new AI(*this, render_, PADDLESPEED, WINDOWHEIGHT, WINDOWWIDTH));
	ball = std::unique_ptr<Ball>(new Ball(*this, render_, BALLSPEED, WINDOWHEIGHT, WINDOWWIDTH));
	score = std::unique_ptr<Score>(new Score(*this, render_, WINDOWHEIGHT, WINDOWWIDTH));

	Attach(player.get());
	Attach(ai.get());
	Attach(ball.get());
	Attach(score.get());

	color.r = color.g = color.b = 255;
}

void Game::PlayingGame() {
	SDL_SetRenderDrawColor(*render_.get(), 0x00, 0x00, 0x00, 255);
	isRunning = true;
	static int lastTime = 0;

	while (isRunning) {
		lastFrame = SDL_GetTicks();
		if (lastFrame >= (lastTime + 1000)) {
			lastTime = lastFrame;
			fps = frameCount;
			frameCount = 0;
		}

		CheckPlayerControl();
		Update();
		Render();
	}

	EndGame();
}

void Game::NewRound() {
	Mix_PlayChannel(-1, Mix_LoadWAV("win.wav"), 0);

	Notify("SetPosition");
}

void Game::Update() {
	ai->Move(ball->getRectangle().y, WINDOWHEIGHT);

	switch (ball->CheckPositionAndIntersection(player->getRectangle(), ai->getRectangle(), WINDOWHEIGHT, WINDOWWIDTH)) {
	case 0:
		score->AddPointToPlayer();
		NewRound();
		break;
	case 1:
		score->AddPointToAI();
		NewRound();
		break;
	default:
		break;
	}
}

void Game::CheckPlayerControl() {
	SDL_Event e;
	const Uint8* keystates = SDL_GetKeyboardState(NULL);
	while (SDL_PollEvent(&e)) if (e.type == SDL_QUIT) isRunning = false;
	if (keystates[SDL_SCANCODE_ESCAPE]) isRunning = false;

	player->PlayerMovement(keystates, WINDOWHEIGHT);
}

void Game::Render() {
	SDL_SetRenderDrawColor(*render_.get(), 0x00, 0x00, 0x00, 255);
	SDL_RenderClear(*render_.get());

	frameCount++;
	timerFPS = SDL_GetTicks() - lastFrame;
	if (timerFPS < (1000 / 60)) {
		SDL_Delay((1000 / 60) - timerFPS);
	}

	SDL_SetRenderDrawColor(*render_.get(), color.r, color.g, color.b, 255);

	Notify("Render");

	SDL_RenderPresent(*render_.get());
}

void Game::EndGame() {
	Mix_HaltMusic();
	SDL_DestroyRenderer(*render_.get());
	SDL_DestroyWindow(window);
	Mix_Quit();
	SDL_Quit();
}