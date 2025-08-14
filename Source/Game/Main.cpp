#include "Game/SpaceGame.h"

int main(int argc, char* argv[]) { 

    // load the json data from a file
    std::string buffer;
    fox::file::ReadTextFile("json.txt", buffer);
    // show the contents of the json file (debug)
    std::cout << buffer << std::endl;

    // create json document from the json file contents
    rapidjson::Document document;
    fox::json::Load("json.txt", document);    

    std::string name;
    int age;
    float speed;
    bool isAwake;
    fox::vec2 position;
    fox::vec3 color;

    JSON_READ(document, name);
    JSON_READ(document, age);
    JSON_READ(document, speed);
    JSON_READ(document, isAwake);
    JSON_READ(document, position);
    JSON_READ(document, color);

    // show the data
    std::cout << name << " " << age << " " << speed << " " << isAwake << std::endl;
    std::cout << position.x << " " << position.y << std::endl;
    std::cout << color.r << " " << color.g << " " << color.b << " " << std::endl;

	return 0;

    // Initize Engine 
	fox::Logger::Info("initialize engine");
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

    auto background = fox::Resources().Get<fox::Texture>("Textures/space-was-cool.png", fox::GetEngine().GetRenderer());

    float screenW = (float)fox::GetEngine().GetRenderer().GetWidth();
    float screenH = (float)fox::GetEngine().GetRenderer().GetHeight();


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

        // draw Startup
        fox::vec3 color{ 0,0,0 };
        fox::GetEngine().GetRenderer().SetColor(color.r, color.g, color.b);
        fox::GetEngine().GetRenderer().Clear();        

        fox::GetEngine().GetRenderer().DrawTextureBG(background.get(), 0, screenW, screenH);

        // draw Game
        game->Draw(fox::GetEngine().GetRenderer());
        
		

       ///////////////////////////////////

        fox::GetEngine().GetRenderer().Present();
    }
       
    game->Shutdown();
    game.release(); 
    fox::GetEngine().Shutdown();
    
   
    return 0;
};