#include "Character.h"
Character::Character(Body* body, SDL_Surface* sprite) {
	physics = body;
	characterImage = sprite;
}

Character::~Character() {

}

bool Character::onCreate() {
	return true;
}

void Character::onDestroy() {
	//don't want those memory leaks
	delete physics;
	delete characterImage;
}

void Character::Update(const float deltatime) {
	//applies gravity to character and updates the body
	physics->ApplyForce(Vec3(0.0f, -9.8f, 0.0f));
	physics->Update(deltatime);
}

void Character::Render() const {
}

void Character::HandleEvents(const SDL_Event& event) {
	//handles character movement
	if (event.type == SDL_KEYDOWN) {
		switch (event.key.keysym.scancode) {
		case SDL_SCANCODE_A:
			printf("A is pressed\n");
			physics->ApplyForce(Vec3(-5.0f, 0.0f, 0.0f));
			break;
		case SDL_SCANCODE_D:
			printf("D is pressed\n");
			physics->ApplyForce(Vec3(5.0f, 0.0f, 0.0f));
			break;
		case SDL_SCANCODE_SPACE:
			printf("SPACE is pressed\n");
			physics->ApplyForce(Vec3(0.0f, 20.0f, 0.0f));
			break;
		default:
			break;
		}
	}
}