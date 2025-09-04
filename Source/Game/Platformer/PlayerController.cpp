#include "../GamePCH.h"
#include "PlayerController.h"	

FACTORY_REGISTER(PlayerController)

void PlayerController::Start(){
	rigidBody = owner->GetComponent<fox::RigidBody>();
}

void PlayerController::Update(float dt){

	float dir = 0;
	if (fox::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_A)) dir = -1;
	if (fox::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_D)) dir = +1;

	if (dir != 0) {
		rigidBody->ApplyForce(fox::vec2{ 1, 0 } * dir * speed);
		if (rigidBody->velocity.x > maxSpeed) rigidBody->velocity.x = maxSpeed;
		if (rigidBody->velocity.x < -maxSpeed) rigidBody->velocity.x = -maxSpeed;
	}

	if (fox::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_SPACE)) {
		rigidBody->ApplyForce(fox::vec2{ 0, -1 } * jump);
	}

	auto spriteRenderer = owner->GetComponent<fox::SpriteRenderer>();
	if (spriteRenderer) {
		if (fox::math::fabs(rigidBody->velocity.x) > 0)
			spriteRenderer->flipH = (rigidBody->velocity.x < 0);
	}
}

void PlayerController::OnCollision(fox::Actor* other){
	std::cout << other->name << std::endl;
}

void PlayerController::Read(const fox::json::value_t& value){
	Object::Read(value);

	JSON_READ(value, speed);
	JSON_READ(value, maxSpeed);
	JSON_READ(value, jump);
	JSON_READ(value, fireTime);
}
