#pragma once
#include "Framework/Component.h"

namespace fox {
	class ColliderComponent : public Component {

	public:
		virtual bool CheckCollision(ColliderComponent& other) = 0;
	};
}