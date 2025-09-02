#pragma once  
#include "Core/Serializable.h"

namespace fox {
	class ICollidable {
	public:
		virtual ~ICollidable() = default;

		virtual void OnCollision(class Actor* other) = 0;
	};
}