#include "Math/Math.h"
#include "Math/Vector2.h"
#include "Math/Vector3.h"
#include "Math/Transform.h"
#include "Core/Time.h"
#include "Core/Random.h"
#include "Renderer/Renderer.h"
#include "Renderer/Model.h"
#include "Input/InputSystem.h"
#include "Audio/AudioSystem.h"
#include "Framework/Actor.h"
#include "Framework/Scene.h"
#include "Engine.h"
#include "Renderer/Text.h"
#include "Renderer/Font.h"
#include "Core/File.h"
#include "Renderer/Texture.h"

#include "Game/Player.h"
#include "Game/SpaceGame.h"

#include <iostream>
#include <vector>
#include <fmod.hpp>
#include <memory>

int main(int argc, char* argv[]) {

	// Initize Engine   
    fox::GetEngine().Initialize();

    // Initialize Game
	std::unique_ptr<fox::Game> game = std::make_unique<SpaceGame>();
	game->Initialize();

	// Load a sound file
	     

    // Create stars
	std::vector<fox::vec2> stars;
    for (int i = 0; i < 100; i++) {
        stars.push_back(fox::vec2{ fox::random::getReal() * 1280, fox::random::getReal() * 1024 });
    }

    //Load Font
	fox::Font* font = new fox::Font();
    font->Load("arcadeclassic.ttf", 20);

    // create texture, using shared_ptr so texture can be shared
    std::shared_ptr<fox::Texture> texture = std::make_shared<fox::Texture>();
    texture->Load("foodery.png", fox::GetEngine().GetRenderer());

    SDL_Event e;
    bool quit = false;

    while (!quit) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_EVENT_QUIT) {
                quit = true;
            }
        }

        fox::GetEngine().Update();
        game->Update(fox::GetEngine().GetTime().GetDeltaTime());

        if(fox::GetEngine().GetInput().GetKeyPressed(SDL_SCANCODE_ESCAPE)) {
            quit = true;
        }

        fox::GetEngine().GetInput().Update();
        fox::GetEngine().GetAudio().Update();

        /////////////////////////////////
        
        //Escape Key

        // draw
        fox::vec3 color{ 0,0,0 };
        fox::GetEngine().GetRenderer().SetColor(color.r, color.g, color.b);
        fox::GetEngine().GetRenderer().Clear();
        fox::GetEngine().GetRenderer().DrawTexture(texture.get(), 1, 1);

        game->Draw(fox::GetEngine().GetRenderer());
		

       ///////////////////////////////////

        fox::GetEngine().GetRenderer().Present();
    }
       
    game->Shutdown();
    game.release(); 
    fox::GetEngine().Shutdown();
    
   
    return 0;
};