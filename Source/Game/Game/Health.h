#pragma once
#include "Framework/Actor.h"
#include "Math/Transform.h"

class Health : public fox::Actor {
public:
	float speed = 200.0f;

public:
	Health() = default;
	Health(const fox::Transform& transform, fox::res_t<fox::Texture> texture) :
		Actor{ transform, texture }
	{
	};

	void Initialize();

	void Update(float dt) override;

	// Inherited via Actor
	void OnCollision(Actor* other) override;
};