#include "../GamePCH.h"
#include "EnemyController.h"	

FACTORY_REGISTER(EnemyController)

void EnemyController::Start() {
	rigidBody = owner->GetComponent<fox::RigidBody>();
}

void EnemyController::Update(float dt) {

	float dir = 0;

	// move towards player
	auto player = owner->scene->GetActorByName<fox::Actor>("platformplayer");
	if (player) {
		if (player->transform.position.x < owner->transform.position.x) dir = -1;
		else dir = 1;
	}

	if (dir != 0) {
		rigidBody->ApplyForce(fox::vec2{ 1, 0 } *dir * 500);
	}
}

void EnemyController::OnCollision(fox::Actor* other) {
	if (other->tag == "player") {
		owner->destroyed = true;
		EVENT_NOTIFY_DATA(add_points, 50);
	}
}	

void EnemyController::Read(const fox::json::value_t& value) {
	Object::Read(value);

	JSON_READ(value, speed);
	JSON_READ(value, maxSpeed);
	JSON_READ(value, jump);
	JSON_READ(value, fireTime);
}
