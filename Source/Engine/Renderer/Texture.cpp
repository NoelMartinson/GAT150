#include "Texture.h"
#include <iostream>

fox::Texture::~Texture()
{
    // if texture exists, destroy texture
    if (texture != NULL) SDL_DestroyTexture(texture);
}

bool fox::Texture::Load(const std::string& filename, Renderer& renderer)  
{  
    // load image onto surface  
    SDL_Surface* surface = IMG_Load(filename.c_str());  
    if (surface == NULL)  
    {  
        std::cerr << "Could not load image: " << filename << std::endl;  
        return false;  
    }  

    // create texture from surface, texture is a friend class of renderer  
    texture = SDL_CreateTextureFromSurface(renderer.renderer, surface);  
    // once texture is created, surface can be freed up  
    SDL_DestroySurface(surface);  
    if (texture == NULL)  
    {  
        std::cerr << "Could not create texture: " << filename << std::endl;  
        return false;  
    }  

    return true;  
}

fox::vec2 fox::Texture::GetSize()  
{  
    if (texture == nullptr) return fox::vec2{ 0, 0 };  

    float width, height;  
    SDL_GetTextureSize(texture, &width, &height);  
    return fox::vec2{ width, height };  
}