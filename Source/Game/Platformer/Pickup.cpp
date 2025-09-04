#include "Pickup.h"

FACTORY_REGISTER(Pickup)

void Pickup::Start() {
	rigidBody = owner->GetComponent<fox::RigidBody>();
}

void Pickup::Update(float dt) {
}

void Pickup::OnCollision(fox::Actor* other) {
	if (other->tag == "player") {
		owner->destroyed = true;
		EVENT_NOTIFY_DATA(add_points, 50);
		fox::GetEngine().GetAudio().PlaySound("coin");
	}
}

void Pickup::Read(const fox::json::value_t& value) {
	Object::Read(value);
}