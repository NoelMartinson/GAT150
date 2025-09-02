#pragma once
#include "ColliderComponent.h"
#include "Core/Json.h"

namespace fox {
	class CircleCollider2D : public ColliderComponent {
	public:
		float radius{ 0 };

	public:
		CLASS_PROTOTYPE(CircleCollider2D)

		void Update(float dt) override;
		virtual bool CheckCollision(ColliderComponent& other) override;

		void Read(const json::value_t& value) override;
	};
}
