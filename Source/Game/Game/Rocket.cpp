#include "Rocket.h"
#include "Engine.h"
#include "Player.h"
#include "../GamePCH.h"

FACTORY_REGISTER(Rocket)

void Rocket::Update(float dt) {
	fox::vec2 force = fox::vec2{ 1, 0 }.Rotate(fox::math::degToRad(owner->transform.rotation)) * speed;


	auto rb = owner->GetComponent<fox::RigidBody>();
	if (rb) {
		rb->SetVelocity(force);
	}

	owner->transform.position.x = fox::math::wrap(owner->transform.position.x, 0.0f, (float)fox::GetEngine().GetRenderer().GetWidth());
	owner->transform.position.y = fox::math::wrap(owner->transform.position.y, 0.0f, (float)fox::GetEngine().GetRenderer().GetHeight());

	
}

void Rocket::OnCollision(fox::Actor* other)
{
	if (owner->tag != other->tag) {
		owner->destroyed = true;
	}
}
void Rocket::Read(const fox::json::value_t& value){
	Object::Read(value);

	JSON_READ(value, speed);
	JSON_READ(value, lifespan);
}