#pragma once
#include "GameObject.h"

class GameRectangle : public GameObject {
public:
	GameRectangle() = delete;
	GameRectangle(Subject& subject, std::shared_ptr<SDL_Renderer*> render_ptr, int speed, int windowHeight, int windowWidth);

	int getSpeed() const;
	void setSpeed(int new_speed);

	SDL_Rect getRectangle() const;
	void setRectangle(SDL_Rect new_rectangle);
	virtual void SetPosition();

	void Render() override;

	void Update(const std::string& message_from_subject) override;

protected:
	SDL_Rect rectangle = { 0, 0, 0, 0 };
	
	int speed = 0;
	int startXPosition = 0;
	int startYPosition = 0;
};