#include "Texture.h"
#include "Renderer.h"
#include "Resource/Resource.h"
#include "Core/Logger.h"
#include <iostream>

fox::Texture::~Texture()
{
    // if texture exists, destroy texture
    if (texture != nullptr) SDL_DestroyTexture(texture);
}

bool fox::Texture::Load(const std::string& filename, Renderer& renderer)  
{  
    // load image onto surface  
    SDL_Surface* surface = IMG_Load(filename.c_str());  
    if (surface == NULL)  
    {  
        Logger::Error("Could not load image: {}", SDL_GetError());       
        return false;  
    }  

    // create texture from surface, texture is a friend class of renderer  
    texture = SDL_CreateTextureFromSurface(renderer.renderer, surface);  
    // once texture is created, surface can be freed up  
    SDL_DestroySurface(surface);  
    if (texture == NULL)  
    {  
        Logger::Error("Could not create texture: {}", filename); // Fixed 'fileName' to 'filename'
        return false;  
    }  

    return true;  
}

fox::vec2 fox::Texture::GetSize()  
{   
    float width, height;  
    SDL_GetTextureSize(texture, &width, &height);  
    return fox::vec2{ width, height };  
}