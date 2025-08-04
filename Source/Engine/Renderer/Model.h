#pragma once
#include "../Math/Vector2.h"
#include "../Math/Vector3.h"
#include "../Math/Transform.h"

#include <vector>

namespace fox {
	class Model {
	public:
		Model() = default;
		Model(const std::vector<vec2>& points, const vec3& color = { 1, 1, 1 })
			: points(points),
			color(color) 
		{
			CalculateRadius();
		}
	
		void Draw(class Renderer& renderer, const vec2& position,float rotation, float scale);
		void Draw(class Renderer& renderer, const Transform& transform);

		float GetRadius() const {return radius;}

	private:
		void CalculateRadius();

	private:
		std::vector<vec2> points;
		float radius{ 0 };
		vec3 color{ 1, 1, 1};
	};
}