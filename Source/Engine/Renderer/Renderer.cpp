#include <iostream>
#include "Renderer.h"

namespace fox
{
    bool Renderer::Initialize() {

        if (!SDL_Init(SDL_INIT_VIDEO)) {
            std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
            return false;
        }

        if (!TTF_Init()) {
            std::cerr << "TTF_Init Error: " << SDL_GetError() << std::endl;
            return false;
        }

        return true;
    }

    bool Renderer::CreateWindow(const std::string& name, int width, int height) {

        m_width = width;
		m_height = height; 

        window = SDL_CreateWindow(name.c_str(), width, height, 0);
        if (window == nullptr) {
            std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
            SDL_Quit();
            return false;
        }

        renderer = SDL_CreateRenderer(window, NULL);
        if (renderer == nullptr) {
            std::cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
            SDL_DestroyWindow(window);
            SDL_Quit();
            return false;
        }

        return true;
    }

    void Renderer::SetColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
        SDL_SetRenderDrawColor(renderer, r, g, b, a);
    }

    void Renderer::SetColor(float r, float g, float b, float a)
    {
        SDL_SetRenderDrawColorFloat(renderer, r, g, b, a);
    }

    void Renderer::Clear() {
        SDL_RenderClear(renderer);
    }

    void Renderer::Present() {
        SDL_RenderPresent(renderer);
    }

    void Renderer::Shutdown() {
        TTF_Quit();
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
    }

    void Renderer::DrawLine(float x1, float y1, float x2, float y2) {
        SDL_RenderLine(renderer, x1, y1, x2, y2);
    }

    void Renderer::DrawPoint(float x1, float y1) {
        SDL_RenderPoint(renderer, x1, y1);
	}
}