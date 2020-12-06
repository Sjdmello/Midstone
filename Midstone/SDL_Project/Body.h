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
public:
	Body(Vec3 _position, Vec3 _velocity, Vec3 _acceleration, float _mass);
	~Body();

	void Update(const float deltaTime);
	void ApplyForce(Vec3 Force);

	inline Vec3 GetPos() { return position; }
	inline Vec3 GetVel() { return velocity; }
	inline Vec3 GetAccel() { return acceleration; }
	inline float GetRad() { return r; }

	inline void SetPos(Vec3 newPos) { position = newPos; }
	inline void SetVel(Vec3 newVel) { velocity = newVel; }
	inline void SetAccel(Vec3 newAccel) { acceleration = newAccel; }
	inline void SetRad(float newRad) { r = newRad; }
};
#endif