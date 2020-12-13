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
	CharacterOnGround = false;
	CanJump = false;

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

	//printf("%f %f %f \n", physics->GetPos().x, physics->GetPos().y, physics->GetPos().z);
	//system.debug(physics->GetVel());
	system.debug(physics->GetPos());

	if (physics->GetPos().y == 37.0f) {
		CharacterOnGround = true;
	}
	if (CharacterOnGround == true) {
		CanJump = true;
	}


	if (tickSwapper) {
		//applies gravity to character.
		if (!CharacterOnGround) {
			physics->ApplyForce(Vec3(0.0f, -2.0f, 0.0f));
		}
		else
		{
			physics->SetVel(Vec3(currentVel.x, 0.0f, currentVel.z));
		}
	} else {
		//applies movement to character.
		physics->ApplyForce(moveDir);
	}
	
	currentVel = physics->GetVel();

	//sets a cap on the velocity.
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
	CharacterOnGround = false;
	//moveDir = Vec3(0.0f, 0.0f, 0.0f);
}

void Character::Render() const {
}

void Character::HandleEvents(const SDL_Event& event) {
	//handles character movement
	if (event.type == SDL_KEYDOWN) {
		switch (event.key.keysym.scancode) {
		case SDL_SCANCODE_A:
			moveDir = Vec3(-15.0f, 0.0f, 0.0f);
			isMoving = true;
			break;
		case SDL_SCANCODE_D:
			moveDir = Vec3(15.0f, 0.0f, 0.0f);
			isMoving = true;
			break;
		case SDL_SCANCODE_SPACE:
			if (CanJump == true) {
				moveDir = Vec3(0.0f, 80.0f, 0.0f);
				CanJump = false;
				CharacterOnGround = false;
			}

			break;
		default:
			break;
		}
	}

	//detects when character stops getting horizontal input so the character can slow to a stop.
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