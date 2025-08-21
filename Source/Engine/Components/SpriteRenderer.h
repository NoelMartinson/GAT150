#pragma once
#include "RendererComponent.h"
#include "Core/Json.h"

namespace fox {
	class SpriteRenderer : public RendererComponent {
	public:
		std::string textureName;

	public:
		void Update(float dt) override;
		void Draw(Renderer& renderer) override;

		void Read(const json::value_t& value);
	};
}