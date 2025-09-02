#pragma once
#include "Framework/Component.h"
#include "Core/Json.h"

namespace fox {
	class RigidBody : public Component {
	public:
		vec2 velocity{0,0};
		float dampening{ 0 };
	public:
		CLASS_PROTOTYPE(RigidBody)

		void Update(float dt) override;
		void Read(const json::value_t& value);
	};
}
