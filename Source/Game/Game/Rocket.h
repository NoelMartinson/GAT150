#pragma once
#include "Framework/Actor.h"

class Rocket : public fox::Actor {
public:
	float speed = 200;
public:
	Rocket() = default;
	Rocket(const fox::Transform& transform, std::shared_ptr<fox::Model> model) :
		Actor{ transform, model }
	{
	}

	void Update(float dt) override;


	// Inherited via Actor
	void OnCollision(Actor* other) override;

};