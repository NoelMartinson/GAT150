#pragma once
#include "Framework/Component.h"
#include "Renderer/Renderer.h"

namespace fox {
	class RendererComponent : public Component {
	public:
		virtual void Draw(class Renderer& renderer) = 0;
	};
}