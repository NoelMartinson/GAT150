#pragma once
#include "Framework/Actor.h"
#include "Math/Transform.h"

class Enemy : public fox::Actor {
public:
	float speed = 200.0f;

public:
	Enemy() = default;
	Enemy(const fox::Transform& transform, std::shared_ptr<fox::Model> model) :
		Actor{ transform, model }
	{
	};

	void Update(float dt) override;

	// Inherited via Actor
	void OnCollision(Actor* other) override;
};