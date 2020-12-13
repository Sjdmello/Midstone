#include "SpikeBall.h"

SpikeBall::SpikeBall(Body* body, SDL_Surface* sprite, float minHeight, float maxHeight) {
	physics = body;
	image = sprite;
	minY = minHeight;
	maxY = maxHeight;

	onCreate();
}

SpikeBall::~SpikeBall() {
}

bool SpikeBall::onCreate() {
	currentVel = Vec3(0.0f, 0.0f, 0.0f);
	velCap = 15.0f;

	return true;
}

void SpikeBall::onDestroy() {
	if (physics) delete physics;
	if (image) delete image;
}

void SpikeBall::Update(const float deltaTime) {
	//moves the spikeball up and down the screen.
	if (physics->GetPos().y < minY) {
		physics->ApplyForce(Vec3(0.0f, 5.0f, 0.0f));
	}
	if (physics->GetPos().y > maxY) {
		physics->ApplyForce(Vec3(0.0f, -5.0f, 0.0f));
	}

	currentVel = physics->GetVel();

	//sets a cap on the velocity.
	if (currentVel.y > velCap) {
		physics->SetVel(Vec3(currentVel.x, velCap - 1.0f, currentVel.z));
	}
	else if (currentVel.y < -velCap) {
		physics->SetVel(Vec3(currentVel.x, -velCap + 1.0f, currentVel.z));
	}

	physics->Update(deltaTime);
}

void SpikeBall::Render() const {
}

void SpikeBall::HandleEvents(const SDL_Event& event) {
}