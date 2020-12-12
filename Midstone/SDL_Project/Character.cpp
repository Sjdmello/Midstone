#include "Character.h"
Character::Character(Body* body, SDL_Surface* sprite) {
	physics = body;
	characterImage = sprite;

	onCreate();
}

Character::~Character() {

}

bool Character::onCreate() {
	moveDir = Vec3(0.0f, 0.0f, 0.0f);
	currentVel = Vec3(0.0f, 0.0f, 0.0f);
	tickSwapper = true;
	velCap = 20.0f;
	isMoving = false;

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
		//applies gravity to character.
		physics->ApplyForce(Vec3(0.0f, -10.0f, 0.0f));
	} else {
		//applies movement to character.
		physics->ApplyForce(moveDir);
	}
	
	currentVel = physics->GetVel();

	//sets a cap on the velocity
	currentVel = physics->GetVel();
	if (currentVel.x > velCap) {
		physics->SetVel(Vec3(velCap -1.0f, currentVel.y, currentVel.z));
	} else if (currentVel.x < -velCap) {
		physics->SetVel(Vec3(-velCap + 1.0f, currentVel.y, currentVel.z));
	}
	if (currentVel.y > velCap) {
		physics->SetVel(Vec3(currentVel.x, velCap - 1.0f, currentVel.z));
	} else if (currentVel.y < -velCap) {
		physics->SetVel(Vec3(currentVel.x, -velCap + 1.0f, currentVel.z));
	}

	//making the character slow to a stop a few frames after release of button.
	if (!isMoving) {
		if (currentVel.x >= 1.0f) {
			physics->SetVel(Vec3(currentVel.x - 0.5f, currentVel.y, currentVel.z));
		} else if (currentVel.x <= 1.0f && currentVel.x > 0.0f) {
			physics->SetVel(Vec3(0.0f, currentVel.y, currentVel.z));
		}
		if (currentVel.x <= -1.0f) {
			physics->SetVel(Vec3(currentVel.x + 0.5f, currentVel.y, currentVel.z));
		} else if (currentVel.x >= -1.0f && currentVel.x < 0.0f) {
			physics->SetVel(Vec3(0.0f, currentVel.y, currentVel.z));
		}
	}

	//update and switch active frame.
	physics->Update(deltatime);
	tickSwapper = !tickSwapper;
}

void Character::Render() const {
}

void Character::HandleEvents(const SDL_Event& event) {
	//handles character movement
	if (event.type == SDL_KEYDOWN) {
		switch (event.key.keysym.scancode) {
		case SDL_SCANCODE_A:
			//printf("A is pressed\n");
			moveDir = Vec3(-20.0f, 0.0f, 0.0f);
			isMoving = true;
			break;
		case SDL_SCANCODE_D:
			//printf("D is pressed\n");
			moveDir = Vec3(20.0f, 0.0f, 0.0f);
			isMoving = true;
			break;
		case SDL_SCANCODE_SPACE:
			//printf("SPACE is pressed\n");
			moveDir = Vec3(0.0f, 50.0f, 0.0f);
			break;
		default:
			break;
		}
	}

	if (event.type == SDL_KEYUP) {
		switch (event.key.keysym.scancode) {
		case SDL_SCANCODE_A:
			isMoving = false;
			moveDir = Vec3(0.0f, 0.0f, 0.0f);
			break;
		case SDL_SCANCODE_D:
			isMoving = false;
			moveDir = Vec3(0.0f, 0.0f, 0.0f);
			break;
		default:
			break;
		}
		moveDir = Vec3(0.0f, 0.0f, 0.0f);
	}
}