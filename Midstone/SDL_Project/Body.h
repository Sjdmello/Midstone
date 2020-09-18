#ifndef BODY_H
#define BODY_H
#include "Vector.h"
#include "Collider.h"
#include<SDL.h>
using namespace MATH;

class Body {
	friend class Collider;
protected:
	float mass;
	float r;
	Vec3 position;
	Vec3 velocity;
	Vec3 acceleration;
	SDL_Surface* image;
public:
	Body();
	~Body();
	Body(Vec3 _position, Vec3 _velocity, Vec3 _acceleration, float _mass);

	void Update(const float deltaTime, float time, float force);
	void ApplyForce(Vec3 Force);
	Vec3 GetPos();
};
#endif