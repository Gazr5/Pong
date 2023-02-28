#include "GameRectangle.h"

GameRectangle::GameRectangle(Subject& subject, std::shared_ptr<SDL_Renderer*> render_ptr, int speed, int windowHeight, int windowWidth) : GameObject(subject, render_ptr) {
	setSpeed(speed);
	setRectangle({ 0, 0, 20, static_cast<int>(windowHeight / 6) });
	SetPosition();
}

int GameRectangle::getSpeed() const {
	return speed;
}

void GameRectangle::setSpeed(int new_speed) {
	speed = new_speed;
}

SDL_Rect GameRectangle::getRectangle() const {
	return rectangle;
}

void GameRectangle::setRectangle(SDL_Rect new_rectangle) {
	rectangle = new_rectangle;
}

void GameRectangle::SetPosition() {
	rectangle.x = startXPosition;
	rectangle.y = startYPosition;
}

void GameRectangle::Render() {
	SDL_RenderDrawRect(*render_.get(), &rectangle);
	SDL_RenderFillRect(*render_.get(), &rectangle);
}

void GameRectangle::Update(const std::string& message_from_subject) {
	if (message_from_subject == "Render") {
		Render();
	}
	else if (message_from_subject == "SetPosition") {
		SetPosition();
	}
}