#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include <boost/asio.hpp>

#include "game.h"

#include <memory>
#include <string>
#include <iostream>

class Menu {
public:
	Menu();

	void Render();

	void MainMenu();
	void WriteIP(std::string& inputText, SDL_Event& e);
	void StartSingleGame();
	void StartMultiplayerGame(bool ifHost);
private:
	std::string message;
	const size_t hostMenuDefaultText;

	const Uint8* keystates;
	SDL_Renderer* renderer;
	std::shared_ptr<SDL_Renderer*> render_;
	SDL_Window* window;
	SDL_Color color;

	int fontSize = 0;

	TTF_Font* Sans;
	SDL_Texture* texture;
	SDL_Surface* surface;
	SDL_Rect scoreBoard;
	SDL_Color Color;

	boost::asio::io_service service;
};