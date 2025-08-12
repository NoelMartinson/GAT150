#pragma once
#include "Object.h"

namespace fox {
	class Component : public Object {
	public:
		class Actor* owner{ nullptr };

	public:
		Component() = default;

		void Draw();

		virtual void Update(float dt) = 0;
	};
}