#pragma once
#include "../Math/Vector2.h"
#include "Renderer.h"
#include "Resource/Resource.h"

#include <SDL3/SDL.h>
#include <string>

namespace fox {
	class Texture : public Resource {
	public:
		Texture() = default;
		~Texture();

		bool Load(const std::string& filename, class Renderer& renderer);

		vec2 GetSize();

		friend class Renderer;

	private:
		struct SDL_Texture* texture{ nullptr };
	};
}