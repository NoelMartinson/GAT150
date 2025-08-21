#pragma once
#include "Framework/Component.h"
#include "Math/Transform.h"

class Health : public fox::Component {
public:
	float speed = 200.0f;

public:
	Health() = default;
	void Initialize();

	void Update(float dt) override;

	// Inherited via Actor
	void OnCollision(class fox::Actor* other);
};