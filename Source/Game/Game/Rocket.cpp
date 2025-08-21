#include "Rocket.h"
#include "Engine.h"
#include "Player.h"
#include "../GamePCH.h"

FACTORY_REGISTER(Rocket)

void Rocket::Update(float dt) {
	fox::vec2 force = fox::vec2{ 1, 0 }.Rotate(fox::math::degToRad(owner->transform.rotation)) * speed;
	//velocity = force;

	auto rb = owner->GetComponent<fox::RigidBody>();
	if (rb) {
		rb->velocity = force;
	}

	owner->transform.position.x = fox::math::wrap(owner->transform.position.x, 0.0f, (float)fox::GetEngine().GetRenderer().GetWidth());
	owner->transform.position.y = fox::math::wrap(owner->transform.position.y, 0.0f, (float)fox::GetEngine().GetRenderer().GetHeight());

	Component::Update(dt);
}

void Rocket::OnCollision(fox::Actor* other)
{
	if (owner->tag != other->tag) {
		owner->destroyed = true;
	}
};