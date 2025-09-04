#pragma once
#include "Framework/Component.h"

class FlyingEnemyController : public fox::Component, public fox::ICollidable {
public:
	float speed = 500;
	float maxSpeed = 600;
	float jump = 0;
	float fireTime = 0.2f;
	float fireTimer = 0.0f;
	float collisionCooldown = 0.0f;

	fox::RigidBody* rigidBody{ nullptr };

public:
	FlyingEnemyController() = default;
	CLASS_PROTOTYPE(FlyingEnemyController)

		void Start() override;
	void Update(float dt) override;
	void OnCollision(class fox::Actor* other) override;
	void Read(const fox::json::value_t& value) override;
};
