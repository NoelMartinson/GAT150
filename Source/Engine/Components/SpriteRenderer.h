#pragma once
#include "RendererComponent.h"
#include "Core/Json.h"
#include "Math/Rect.h"

namespace fox {
	class SpriteRenderer : public RendererComponent {
	public:
		std::string textureName;
		fox::rect textureRect;
		res_t<Texture> texture;

	public:
		CLASS_PROTOTYPE(SpriteRenderer)

		void Start() override;
		void Update(float dt) override;
		void Draw(Renderer& renderer) override;

		void Read(const json::value_t& value);
	};
}