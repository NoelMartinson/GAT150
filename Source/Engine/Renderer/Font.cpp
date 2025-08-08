#include "Font.h"
#include "Core/Logger.h"

fox::Font::~Font() {
	if (m_ttfFont != nullptr) {
		TTF_CloseFont(m_ttfFont);
	}
}

bool fox::Font::Load(const std::string& name, float fontSize) {
	m_ttfFont = TTF_OpenFont(name.c_str(), fontSize);
	if (m_ttfFont == nullptr) {
		Logger::Error("Could not load font:", SDL_GetError());
		return false;
	}

	return true;
}
