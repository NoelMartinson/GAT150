#pragma once
#include "Framework/Actor.h"

class Rocket : public fox::Actor {
public:
	float speed = 200;
public:
	Rocket() = default;
	Rocket(const fox::Transform& transform, fox::res_t<fox::Texture> texture) :
		Actor{ transform, texture }
	{
	}

	void Update(float dt) override;


	// Inherited via Actor
	void OnCollision(Actor* other) override;

};