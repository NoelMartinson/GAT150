#include "CircleCollider2D.h"

void fox::CircleCollider2D::Update(float dt){
}

bool fox::CircleCollider2D::CheckCollision(ColliderComponent& other) {
	float distance = (owner->transform.position - other.owner->transform.position).Length();

	auto circleCollider = dynamic_cast<CircleCollider2D*>(&other);
	if (circleCollider) {
		float radii = radius + circleCollider->radius;
		if (distance <= radii)
			return true;
	}
	return false;
}
