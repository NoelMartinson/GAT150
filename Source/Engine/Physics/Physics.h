#pragma once
#include <box2d/box2d.h>
#include <memory>

namespace fox {
	inline b2Vec2 to_b2(const vec2& v) { return b2Vec2{ v.x, v.y };	}
	inline vec2 to_vec2(const b2Vec2& v) { return vec2{ v.x, v.y };	}
	
	class Physics {
	public:
		Physics() = default;

		bool Initialize();
		void Shutdown();

		void Update(float dt);

		static vec2 WorldToPixels(const vec2& world) { return world * pixelsPerUnit; }
		static vec2 PixelToWorld(const vec2& pixel) { return pixel / pixelsPerUnit; }

		static void setPixelsPerUnit(float ppu) { pixelsPerUnit = ppu; }

		static float pixelsPerUnit;

	private:
		friend class PhysicsBody;

		b2WorldId worldId;
	};

} 