#pragma once
#include "RendererComponent.h"

namespace fox {
	class MeshRenderer : public RendererComponent {
	public:
		std::string meshName;

	public:
		void Update(float dt) override;
		void Draw(Renderer& renderer) override;
	};
}