#include "Rocket.h"
#include "Engine.h"
#include "Player.h"
#include "../GamePCH.h"

void Rocket::Update(float dt) {
	fox::vec2 force = fox::vec2{ 1, 0 }.Rotate(fox::math::degToRad(transform.rotation)) * speed;
	//velocity = force;

	auto rb = GetComponent<fox::RigidBody>();
	if (rb) {
		rb->velocity = force;
	}

	transform.position.x = fox::math::wrap(transform.position.x, 0.0f, (float)fox::GetEngine().GetRenderer().GetWidth());
	transform.position.y = fox::math::wrap(transform.position.y, 0.0f, (float)fox::GetEngine().GetRenderer().GetHeight());

	Actor::Update(dt); 
}

void Rocket::OnCollision(Actor* other)
{
	if (tag != other->tag) {
		destroyed = true;
	}
};