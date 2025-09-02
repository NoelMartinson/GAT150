#include "../GamePCH.h"
#include "Enemy.h"
#include "Player.h"

FACTORY_REGISTER(Enemy)

void Enemy::Start(){
	OBSERVER_ADD(player_dead);	

    rigidBody = owner->GetComponent<fox::RigidBody>();
}

void Enemy::Update(float dt) {
    fox::Actor* player = owner->scene->GetActorByName<fox::Actor>("player");

    if (player) {
        fox::vec2 direction = player->transform.position - owner->transform.position;
        direction = direction.Normalized();
        owner->transform.rotation = fox::math::radToDeg(direction.Angle());
    }

    fox::vec2 force = fox::vec2{ 1,0 }.Rotate(fox::math::degToRad(owner->transform.rotation)) * speed;
    //velocity += force * dt;
    if (rigidBody) {
        rigidBody->velocity += force * dt;
    }

    owner->transform.position.x = fox::math::wrap(owner->transform.position.x, 0.0f, (float)fox::GetEngine().GetRenderer().GetWidth());
    owner->transform.position.y = fox::math::wrap(owner->transform.position.y, 0.0f, (float)fox::GetEngine().GetRenderer().GetHeight());

    
}

void Enemy::OnCollision(fox::Actor* other) {
    if ( other->name == "rocket") {
        owner->destroyed = true;
		EVENT_NOTIFY_DATA("add_points", 100);
        fox::GetEngine().GetAudio().PlaySound("edeath");

    }
}

void Enemy::Read(const fox::json::value_t& value){
	Object::Read(value);

	JSON_READ(value, speed);
}

void Enemy::OnNotify(const fox::Event& event){
    if (fox::equalsIgnoreCase(event.id, "player_dead")) {
        speed = 0;
	}
}
