#pragma once
#include "Framework/Component.h"

class Rocket : public fox::Component {
public:
	float speed = 200;
public:
	Rocket() = default;
	
	void Update(float dt) override;


	// Inherited via Actor
	void OnCollision(class fox::Actor* other);

};