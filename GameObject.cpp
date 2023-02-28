#include "GameObject.h"

GameObject::GameObject(Subject& subject, std::shared_ptr<SDL_Renderer*> render_ptr) : subject_(subject) {
	subject_.Attach(this);
	render_ = render_ptr;
}

void GameObject::Update(const std::string& message_from_subject) {
	if (message_from_subject == "Render") {
		Render();
	}
}