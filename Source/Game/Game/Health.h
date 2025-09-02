#pragma once
#include "Framework/Component.h"
#include "Math/Transform.h"

class Health : public fox::Component, public fox::ICollidable {
public:
	float speed = 200.0f;

	fox::RigidBody* rigidBody{ nullptr };

public:
	Health() = default;
	CLASS_PROTOTYPE(Health)
	void Initialize();

	void Update(float dt) override;

	void OnCollision(class fox::Actor* other) override;

	void Read(const fox::json::value_t& value) override;
};