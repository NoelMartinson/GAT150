#pragma once
#include "Framework/Component.h"
#include "Math/Transform.h"

class PlayerController : public fox::Component, public fox::ICollidable {
public:
	float speed = 0;
	float maxSpeed = 0;
	float jump = 0;
	float fireTime = 0.2f;
	float fireTimer = 0.0f;

	fox::RigidBody* rigidBody{ nullptr };

public:
	PlayerController() = default;
	CLASS_PROTOTYPE(PlayerController)

	void Start() override;
	void Update(float dt) override;

	void OnCollision(class fox::Actor* other) override;

	void Read(const fox::json::value_t& value) override;
};