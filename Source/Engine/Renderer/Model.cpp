#include "Model.h"
#include "../Renderer/Renderer.h"

namespace fox {
	void Model::Draw(class Renderer& renderer, const vec2& position,float rotation, float scale) {
		if (points.empty()) return;

		renderer.SetColor(color.r, color.g, color.b);
		for( int i = 0; i < points.size() - 1; i++) {
			vec2 p1 = (points[i].Rotate(math::degToRad(rotation)) * scale) + position;
			vec2 p2 = (points[i + 1].Rotate(math::degToRad(rotation)) * scale) + position;

			renderer.DrawLine(p1.x, p1.y, p2.x, p2.y);
		}	
	}

	void Model::Draw(Renderer& renderer, const Transform& transform) {
		Draw(renderer, transform.position, transform.rotation, transform.scale);
	}
	void Model::CalculateRadius()
	{
		radius = 0;
		for (const auto& point : points) {
			float length = point.Length();
			if (length > radius) radius = length;
		}
	}
	;
}