#pragma once
#include "Framework/Component.h"

namespace fox {
	class RigidBody : public Component {
	public:
		vec2 velocity{0,0};
		float dampening{ 0 };
	public:
		void Update(float dt) override;
	};
}
