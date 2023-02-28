#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include "subject.h"

class GameObject : public IObserver {
public:
	GameObject() = delete;
	GameObject(Subject& subject, std::shared_ptr<SDL_Renderer*> render_ptr);

	virtual void Update(const std::string& message_from_subject) = 0;

	virtual void Render() = 0;
protected:
	Subject& subject_;
	std::shared_ptr<SDL_Renderer*> render_;
};