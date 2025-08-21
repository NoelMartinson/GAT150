#pragma once
#include "ColliderComponent.h"
#include "Core/Json.h"

namespace fox {
	class CircleCollider2D : public ColliderComponent {
	public:
		virtual bool CheckCollision(ColliderComponent& other) override;

		// Inherited via ColliderComponent
		void Update(float dt) override;

		void Read(const json::value_t& value) override;
	};
}
