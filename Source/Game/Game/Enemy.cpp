#include "../GamePCH.h"
#include "Enemy.h"
#include "Player.h"

void Enemy::Update(float dt) {
    Player* player = scene->GetActorByName<Player>("player");

    if (player) {
        fox::vec2 direction = player->transform.position - transform.position;
        direction = direction.Normalized();
        transform.rotation = fox::math::radToDeg(direction.Angle());
    }

    fox::vec2 force = fox::vec2{ 1,0 }.Rotate(fox::math::degToRad(transform.rotation)) * speed;
    //velocity += force * dt;
	auto rb = GetComponent<fox::RigidBody>();
    if (rb) {
        rb->velocity += force * dt;
    }

    transform.position.x = fox::math::wrap(transform.position.x, 0.0f, (float)fox::GetEngine().GetRenderer().GetWidth());
    transform.position.y = fox::math::wrap(transform.position.y, 0.0f, (float)fox::GetEngine().GetRenderer().GetHeight());

    Actor::Update(dt);
}

void Enemy::OnCollision(Actor* other) {
    if (other->tag == "player" && other->name == "rocket") {
        destroyed = true;
        scene->GetGame()->AddPoints(100);
        fox::GetEngine().GetAudio().PlaySound("edeath");

    }
}
