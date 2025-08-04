#pragma once
#include <SDL3_ttf/SDL_ttf.h>
#include <string>
#include <iostream>
#include <SDL3/SDL.h>

struct TTF_Font;
namespace fox
{
	class Font {
	public:
		Font() = default;
		~Font();

		bool Load(const std::string& name, float fontSize);

	private:
		friend class Text;

		TTF_Font* m_ttfFont{ nullptr };
	};
}