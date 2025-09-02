#pragma once
#include "Framework/Component.h"
#include "Math/Transform.h"

class Enemy : public fox::Component, public fox::ICollidable, public fox::IObserver {
public:
	float speed = 200.0f;

	fox::RigidBody* rigidBody{ nullptr };

public:
	Enemy() = default;
	CLASS_PROTOTYPE(Enemy)

	void Start() override;
	void Update(float dt) override;

	void OnCollision(class fox::Actor* other) override;

	void Read(const fox::json::value_t& value) override;

	void OnNotify(const fox::Event& event) override;
};