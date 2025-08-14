#pragma once
#include "ColliderComponent.h"

namespace fox {
	class CircleCollider2D : public ColliderComponent {
	public:
		virtual bool CheckCollision(ColliderComponent& other) override;

		// Inherited via ColliderComponent
		void Update(float dt) override;
	};
}
