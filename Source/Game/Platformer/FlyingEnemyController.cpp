#include "../GamePCH.h"
#include "FlyingEnemyController.h"	

FACTORY_REGISTER(FlyingEnemyController)

void FlyingEnemyController::Start() {
	rigidBody = owner->GetComponent<fox::RigidBody>();
}

void FlyingEnemyController::Update(float dt) {

	// move towards player
	auto player = owner->scene->GetActorByName<fox::Actor>("platformplayer");
	if (player) {
		fox::vec2 direction = player->transform.position - owner->transform.position;
		rigidBody->ApplyForce(direction);
	}

	if (collisionCooldown > 0.0f) {
		collisionCooldown -= dt;
	}
}

void FlyingEnemyController::OnCollision(fox::Actor* other) {
	if (collisionCooldown > 0.0f) return;

	if (other->tag == "player") {
		auto rb = other->GetComponent<fox::RigidBody>();
		if (rb) {
			float speed = rb->velocity.Length();

			if (speed > 800.0f) {
				EVENT_NOTIFY_DATA(add_points, 100);
				fox::GetEngine().GetAudio().PlaySound("hitE");
				collisionCooldown = 1.0f;
			}
			else if (speed < 150.0f) {
				EVENT_NOTIFY(player_hit);
				fox::GetEngine().GetAudio().PlaySound("hitP");
				collisionCooldown = 1.0f;
			}
		}
	}
}




void FlyingEnemyController::Read(const fox::json::value_t& value) {
	Object::Read(value);

	JSON_READ(value, speed);
	JSON_READ(value, maxSpeed);
	JSON_READ(value, jump);
	JSON_READ(value, fireTime);
}
