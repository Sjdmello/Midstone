#include "Body.h"
#include <iostream>
Body::Body() {
	mass = 1.0f;
	position.x = position.y = position.z = 0.0f;
	velocity.x = velocity.y = velocity.z = 0.0f;
	acceleration.x = acceleration.y = acceleration.z = 0.0f;
	r = 1.0f;
}

Body::Body(Vec3 _position, Vec3 _velocity, Vec3 _acceleration, float _mass) {
	position.x = _position.x;
	position.y = _position.y;
	position.z = _position.z;

	velocity.x = _velocity.x;
	velocity.y = _velocity.y;
	velocity.z = _velocity.z;

	acceleration.x = _acceleration.x;
	acceleration.y = _acceleration.y;
	acceleration.z = _acceleration.z;

	r = 1.0f;

	mass = _mass;
}

Body::~Body() {
}

void Body::Update(const float deltatime, float time, float force) {

	position.x += velocity.x * deltatime + 0.5f * acceleration.x * deltatime * deltatime;
	velocity.x += acceleration.x * deltatime;

	position.y += velocity.y * deltatime + 0.5f * acceleration.y * deltatime * deltatime;
	velocity.y += acceleration.y * deltatime;

	position.z += velocity.z * deltatime + 0.5f * acceleration.z * deltatime * deltatime;
	velocity.z += acceleration.z * deltatime;

	//printf("%f   %f   %f   %f   %f\n", time, force, acceleration.x, velocity.x, position.x);
}

void Body::ApplyForce(Vec3 force) {
	acceleration.x = force.x / mass;
	acceleration.y = force.y / mass;
	acceleration.z = force.z / mass;
}

Vec3 Body::GetPos() {
	return position;
}
