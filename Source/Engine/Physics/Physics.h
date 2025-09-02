#pragma once
#include <box2d/box2d.h>
#include <memory>

namespace fox {
	class Physics {
	public:
		Physics() = default;

		bool Initialize();
		void Shutdown();

		void Update(float dt);

	private:
		b2WorldId m_worldId;
	};
} 