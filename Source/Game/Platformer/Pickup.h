#pragma once
#include "EnginePCH.h"
#include "Framework/Component.h"

class Pickup : public fox::Component, public fox::ICollidable {
public:
	fox::RigidBody* rigidBody{ nullptr };

public:
	Pickup() = default;
	CLASS_PROTOTYPE(Pickup)
		void Start() override;
	void Update(float dt) override;
	void OnCollision(class fox::Actor* other) override;
	void Read(const fox::json::value_t& value) override;
};