#pragma once
#include "Framework/Component.h"
#include "Math/Transform.h"

class Player : public fox::Component {
public:
	float speed = 200;
	float rotateRate = 180;
	float fireTime = 0.2f;
	float fireTimer = 0.0f;
	
public:
	Player() = default;
	
	void Initialize();
	void Update(float dt) override;
		
	void OnCollision(class fox::Actor* other);

	void Read(const fox::json::value_t& value) override;
};