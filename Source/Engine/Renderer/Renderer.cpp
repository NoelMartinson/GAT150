#include "Renderer.h"

namespace fox
{
    bool Renderer::Initialize() {

        if (!SDL_Init(SDL_INIT_VIDEO)) {
            Logger::Error("SDL_Init Error: {}", SDL_GetError());
            return false;
        }

        if (!TTF_Init()) {
            Logger::Error("TTF_Init Error: {}", SDL_GetError());       
            return false;
        }

        return true;
    }

    bool Renderer::CreateWindow(const std::string& name, int width, int height, bool fullscreen) {

        m_width = width;
		m_height = height; 

        window = SDL_CreateWindow(name.c_str(), width, height, fullscreen ? SDL_WINDOW_FULLSCREEN: 0);
        if (window == nullptr) {
            Logger::Error("SDL_CreateWindow Error: {}", SDL_GetError());
            SDL_Quit();
            return false;
        }

        renderer = SDL_CreateRenderer(window, NULL);
        if (renderer == nullptr) {
            Logger::Error("SDL_CreateRenderer Error: {}", SDL_GetError());            
            SDL_DestroyWindow(window);
            SDL_Quit();
            return false;
        }

		//SDL_SetRenderLogicalPresentationSize(renderer, width, height, SDL_LOGICAL_PRESENTATION_LETTERBOX);

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
    
    void Renderer::DrawTexture(Texture& texture, float x, float y, float angle)  
    {  
       
        vec2 size = texture.GetSize();

        SDL_FRect destRect;  
        destRect.x = x;  
        destRect.y = y;  
        destRect.w = size.x; 
        destRect.h = size.y;

        SDL_RenderTexture(renderer, texture.texture, NULL, &destRect);  
    }
    void Renderer::DrawTexture(Texture& texture, float x, float y, float angle, float scale)
    {  
        vec2 size = texture.GetSize();  

        SDL_FRect destRect;
        destRect.w = size.x * scale;
        destRect.h = size.y * scale;
        destRect.x = x - (destRect.w * 0.5f);
        destRect.y = y - (destRect.h * 0.5f);

        SDL_RenderTextureRotated(renderer, texture.texture, NULL, &destRect, angle, NULL, SDL_FLIP_NONE);  
    }
    void Renderer::DrawTextureBG(Texture* texture, float x, float y, float angle)
    {
        SDL_FRect dest{ x, y, static_cast<float>(m_width), static_cast<float>(m_height) };
        SDL_RenderTextureRotated(renderer, texture->texture, nullptr, &dest, angle, nullptr, SDL_FLIP_NONE);
    }
}