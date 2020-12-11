#include "Character.h"
Character::Character(Body* body, SDL_Surface* sprite) {
	physics = body;
	characterImage = sprite;
}

Character::~Character() {

}

bool Character::onCreate() {
	moveDir = Vec3(0.0f, 0.0f, 0.0f);
	currentVel = Vec3(0.0f, 0.0f, 0.0f);
	tickSwapper = true;
	velCap = 10.0f;

	return true;
}

void Character::onDestroy() {
	//don't want those memory leaks
	if (physics) delete physics;
	if (characterImage) delete characterImage;
}

void Character::Update(const float deltatime) {
	/*doing this because the applyforce sets the accel directly so if we do multiple applyforce 
	on the same tick it overwrites. We're running at 60fps so it should be fine. */
	if (tickSwapper) {
		//applies 1/30th of gravity to character, runs every other frame
		physics->ApplyForce(Vec3(0.0f, -0.327f, 0.0f));
	} else {
		//applies movement to character
		physics->ApplyForce(moveDir);
	}
	
	//sets a cap of 10 on the velocity
	currentVel = physics->GetVel();
	if (currentVel.x > 20) {
		physics->SetVel(Vec3(19.0f, currentVel.y, currentVel.z));
	} else if (currentVel.x < -20) {
		physics->SetVel(Vec3(-19.0f, currentVel.y, currentVel.z));
	}
	if (currentVel.y > 20) {
		physics->SetVel(Vec3(currentVel.x, 19.0f, currentVel.z));
	} else if (currentVel.y < -20) {
		physics->SetVel(Vec3(currentVel.x, -19.0f, currentVel.z));
	}

	physics->Update(deltatime);

	tickSwapper = !tickSwapper;
	moveDir = Vec3(0.0f, 0.0f, 0.0f);
}

void Character::Render() const {
}

void Character::HandleEvents(const SDL_Event& event) {
	//handles character movement
	if (event.type == SDL_KEYDOWN) {
		switch (event.key.keysym.scancode) {
		case SDL_SCANCODE_A:
			//printf("A is pressed\n");
			moveDir = Vec3(-5.0f, 0.0f, 0.0f);
			break;
		case SDL_SCANCODE_D:
			//printf("D is pressed\n");
			moveDir = Vec3(5.0f, 0.0f, 0.0f);
			break;
		case SDL_SCANCODE_SPACE:
			//printf("SPACE is pressed\n");
			moveDir = Vec3(0.0f, 40.9f, 0.0f);
			break;
		default:
			break;
		}
	}
}