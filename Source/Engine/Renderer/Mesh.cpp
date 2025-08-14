#include "Mesh.h"
#include "../Renderer/Renderer.h"

namespace fox {
	bool Mesh::Load(const std::string& filename)
	{
		std::string buffer;
		if (!file::ReadTextFile(filename, buffer)) {
			Logger::Error("Failed to load mesh file: {}", filename);
			return false;
		}

		std::stringstream stream(buffer);

		stream >> color;

		vec2 point;
		while (stream >> point) {
			points.push_back(point);
		}

		if (!stream.eof()) {
			Logger::Error("Failed to parse mesh file: {}", filename);
			return false;
		}

		return true;
	}
	void Mesh::Draw(class Renderer& renderer, const vec2& position,float rotation, float scale) {
		if (points.empty()) return;

		renderer.SetColor(color.r, color.g, color.b);
		for( int i = 0; i < points.size() - 1; i++) {
			vec2 p1 = (points[i].Rotate(math::degToRad(rotation)) * scale) + position;
			vec2 p2 = (points[i + 1].Rotate(math::degToRad(rotation)) * scale) + position;

			renderer.DrawLine(p1.x, p1.y, p2.x, p2.y);
		}	
	}

	void Mesh::Draw(Renderer& renderer, const Transform& transform) {
		Draw(renderer, transform.position, transform.rotation, transform.scale);
	}
	void Mesh::CalculateRadius()
	{
		radius = 0;
		for (const auto& point : points) {
			float length = point.Length();
			if (length > radius) radius = length;
		}
	}
	;
}