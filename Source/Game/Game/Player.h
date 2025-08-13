#pragma once
#include "Framework/Actor.h"
#include "Math/Transform.h"

class Player : public fox::Actor {
public:
	float speed = 200;
	float rotateRate = 180;
	float fireTime = 0.2f;
	float fireTimer = 0.0f;
	
public:
	Player() = default;
	Player(const fox::Transform& transform, fox::res_t<fox::Texture> texture) :
		Actor{ transform, texture }
	{};

	void Initialize();

	void Update(float dt) override;

	// Inherited via Actor
	void OnCollision(Actor* other) override;


};