#pragma once
#include "../Math/Vector2.h"
#include "../Math/Vector3.h"
#include "../Math/Transform.h"
#include "../Resource/Resource.h"

#include <vector>

namespace fox {
	class Mesh : public Resource {
	public:
		Mesh() = default;
		Mesh(const std::vector<vec2>& points, const vec3& color = { 1, 1, 1 })
			: points(points),
			color(color)
		{
			CalculateRadius();
		}

		bool Load(const std::string& filename);

		void Draw(class Renderer& renderer, const vec2& position, float rotation, float scale);
		void Draw(class Renderer& renderer, const Transform& transform);

		float GetRadius() const { return radius; }

	private:
		void CalculateRadius();

	private:
		float radius{ 0 };
		std::vector<vec2> points;
		vec3 color{ 1, 1, 1 };
	};
}