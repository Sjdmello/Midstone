#include "Collider.h"
#include "VMath.h"

bool Collider::SphereSphereCollision(const Body& body1, const Body& body2) {
	float dist = VMath::distance(body1.position, body2.position);
	printf("%f\n", dist);
	if (dist < (body1.r + body2.r)) {
		return true;
	}
	return false;
}

void Collider::SphereSphereCollisionResponse(Body &body1, Body &body2) {
	float c = 1.0f;
	Vec3 LineOfAction = body1.position - body2.position;
	Vec3 normalizedLineOfAction = VMath::normalize(LineOfAction);
	float v1p = VMath::dot(normalizedLineOfAction, body1.velocity);
	float v2p = VMath::dot(normalizedLineOfAction, body2.velocity);

	if (v1p - v2p > 0.0f) return;

	float v1pnew = (((body1.mass - c * body2.mass) * v1p) + ((1.0f + c) * body2.mass * v2p)) / (body1.mass + body2.mass);
	float v2pnew = (((body2.mass - c * body1.mass) * v2p) + ((1.0f + c) * body1.mass * v1p)) / (body2.mass + body1.mass);

	body1.velocity += (v1pnew - v1p) * normalizedLineOfAction;
	body2.velocity += (v2pnew - v2p) * normalizedLineOfAction;
}
