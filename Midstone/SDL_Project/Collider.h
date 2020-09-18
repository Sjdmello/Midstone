#ifndef COLLIDER_H
#define COLLIDER_H
#include "Body.h"

class Collider{
public:
	friend class Body;
	static bool SphereSphereCollision(const Body &body1, const Body &body2);
	static void SphereSphereCollisionResponse(Body &body1, Body &body2);
};
#endif

