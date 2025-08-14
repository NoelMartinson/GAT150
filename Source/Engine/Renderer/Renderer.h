#pragma once  
#include <SDL3/SDL.h>  
#include <string>  
#include <SDL3_ttf/SDL_ttf.h>  
#include <SDL3_image/SDL_image.h>  
#include "Texture.h"  

namespace fox {  
	class Renderer {  
	public:  
		Renderer() = default;  

		bool Initialize();  
		void Shutdown();  
		bool CreateWindow(const std::string& name, int width, int height, bool fullscreen = false);  

		void Clear();  
		void Present();  

		void SetColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a = 255);  
		void SetColor(float r, float g, float b, float a = 1.0f);  

		void DrawLine(float x1, float y1, float x2, float y2);  
		void DrawPoint(float x1, float y1);  

		int GetWidth() const { return m_width; }  
		int GetHeight() const { return m_height; }  

		void DrawTexture(class Texture& texture, float x, float y, float angle = 0.0f);
        void DrawTexture(class Texture& texture, float x, float y, float angle = 0.0f, float scale = 0.1f);
        void DrawTextureBG(class Texture* texture, float x, float y, float angle = 0.0f);
	private:  
		friend class Text;  
		friend class Texture;  

		int m_width{ 0 };  
		int m_height{ 0 };  

		SDL_Window* window{ nullptr };  
		SDL_Renderer* renderer{ nullptr };  
	};  
};