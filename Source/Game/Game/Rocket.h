#pragma once
#include "Framework/Component.h"

class Rocket : public fox::Component, public fox::ICollidable {
public:
	float speed = 200;
	float lifespan = 2;

	fox::RigidBody* rigidBody{ nullptr };
public:
	Rocket() = default;
	CLASS_PROTOTYPE(Rocket)
	
	void Update(float dt) override;
	
	void OnCollision(class fox::Actor* other) override;

	void Read(const fox::json::value_t& value) override;
};