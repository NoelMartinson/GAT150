#include "../GamePCH.h"
#include "Enemy.h"
#include "Player.h"

FACTORY_REGISTER(Enemy)

void Enemy::Update(float dt) {
    fox::Actor* player = owner->scene->GetActorByName<fox::Actor>("player");

    if (player) {
        fox::vec2 direction = player->transform.position - owner->transform.position;
        direction = direction.Normalized();
        owner->transform.rotation = fox::math::radToDeg(direction.Angle());
    }

    fox::vec2 force = fox::vec2{ 1,0 }.Rotate(fox::math::degToRad(owner->transform.rotation)) * speed;
    //velocity += force * dt;
	auto rb = owner->GetComponent<fox::RigidBody>();
    if (rb) {
        rb->velocity += force * dt;
    }

    owner->transform.position.x = fox::math::wrap(owner->transform.position.x, 0.0f, (float)fox::GetEngine().GetRenderer().GetWidth());
    owner->transform.position.y = fox::math::wrap(owner->transform.position.y, 0.0f, (float)fox::GetEngine().GetRenderer().GetHeight());

    Component::Update(dt);
}

void Enemy::OnCollision(fox::Actor* other) {
    if (other->tag == "player" && other->name == "rocket") {
        owner->destroyed = true;
        owner->scene->GetGame()->AddPoints(100);
        fox::GetEngine().GetAudio().PlaySound("edeath");

    }
}
