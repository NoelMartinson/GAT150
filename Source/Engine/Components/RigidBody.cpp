#include "RigidBody.h"

namespace fox {
	FACTORY_REGISTER(RigidBody)

	void RigidBody::Update(float dt) {
		owner->transform.position += velocity * dt;
		velocity *= (1.0f / (1.0f + dampening * dt));
	}

	void RigidBody::Read(const json::value_t& value) {
		Object::Read(value);

		JSON_READ(value, dampening);
		JSON_READ(value, velocity);
	}
}