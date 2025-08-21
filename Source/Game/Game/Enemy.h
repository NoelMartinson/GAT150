#pragma once
#include "Framework/Component.h"
#include "Math/Transform.h"

class Enemy : public fox::Component {
public:
	float speed = 200.0f;

public:
	Enemy() = default;

	void Update(float dt) override;

	// Inherited via Component
	void OnCollision(class fox::Actor* other) ;
};