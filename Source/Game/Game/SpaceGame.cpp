#include "SpaceGame.h"
#include "Math/Vector2.h"
#include "Renderer/Model.h" 
#include "Renderer/Renderer.h"
#include "Core/Random.h" 
#include "Core/Logger.h"
#include "Player.h"
#include "Enemy.h"
#include "Health.h"
#include "Renderer/ParticleSystem.h"
#include "Input/InputSystem.h"
#include "Framework/Scene.h"
#include "Engine.h"
#include "GameData.h"
#include "Audio/AudioSystem.h"
#include "Resource/ResourceManager.h"


#include <vector>
#include <memory>

bool SpaceGame::Initialize() {

    auto DrawBackground = [&](fox::Texture* tex) {
        fox::GetEngine().GetRenderer().DrawTexture(tex, screenW * 0.5f, screenH * 0.5f, 0, finalScale);
        };


    m_scene = std::make_unique<fox::Scene>(this);

	//titleFont = std::make_shared<fox::Font>();
	//titleFont->Load("ArcadeClassic.ttf", 128);

	//uiFont = std::make_shared<fox::Font>();
	//uiFont->Load("ArcadeClassic.ttf", 48);

    fox::GetEngine().GetAudio().AddSound("music.wav", "music", true);
    fox::GetEngine().GetAudio().AddSound("enemy_death.wav", "edeath", false);
    fox::GetEngine().GetAudio().AddSound("player_death.wav", "pdeath", false);
    fox::GetEngine().GetAudio().AddSound("game_over.wav", "game_over", false);
    fox::GetEngine().GetAudio().AddSound("health.wav", "health", false);

    musicChannel = fox::GetEngine().GetAudio().PlaySound("music");
    musicChannel->setVolume(0.5f);

    auto titleFont = std::make_shared<fox::Font>();
    if (titleFont->Load("ArcadeClassic.ttf", 128.0f)) {
        titleText = std::make_unique<fox::Text>(titleFont);
    }
    else {
        fox::Logger::Error("Failed to load title font.");
        return false;
    }

    auto scoreFont = std::make_shared<fox::Font>();
    if (scoreFont->Load("ArcadeClassic.ttf", 48.0f)) {
        scoreText = std::make_unique<fox::Text>(scoreFont);
    }
    else {
        fox::Logger::Error("Failed to load score font.");
        return false;
    }

    auto livesFont = std::make_shared<fox::Font>();
    if (livesFont->Load("ArcadeClassic.ttf", 48.0f)) {
        livesText = std::make_unique<fox::Text>(livesFont);
    }
    else {
        fox::Logger::Error("Failed to load lives font.");
        return false;
    }

    return true;
}

    void SpaceGame::Update(float dt) {        

        switch (gameState)
        {
        case SpaceGame::GameState::Initalize:
			gameState = SpaceGame::GameState::Title;
            break;
        case SpaceGame::GameState::Title:
            if (fox::GetEngine().GetInput().GetKeyPressed(SDL_SCANCODE_SPACE)) {
				gameState = SpaceGame::GameState::StartGame;
            }
            break;
		case SpaceGame::GameState::StartGame:
            score = 0;
            lives = 3;
			gameState = SpaceGame::GameState::StartRound;
            break;
        case SpaceGame::GameState::StartRound:
        {
            // Player
            fox::Transform transform{ fox::vec2{ fox::GetEngine().GetRenderer().GetWidth() * 0.5f, fox::GetEngine().GetRenderer().GetHeight() * 0.5f}, 0, 2 };
            auto player = std::make_unique<Player>(transform, fox::Resources().Get<fox::Texture>("textures/blue_04.png", fox::GetEngine().GetRenderer()));
            player->speed = 1500.0f;
            player->rotateRate = 180.0f;
            player->dampening = 1.5f;
            player->tag = "player";
            player->name = "player";
            fox::GetEngine().GetAudio().AddSound("rocket.wav", "rocket", false);

            m_scene->AddActor(std::move(player));
			gameState = SpaceGame::GameState::Game;
        }
            break;
        case SpaceGame::GameState::Game:
			enemySpawnTimer -= dt;
            if (enemySpawnTimer <= 0) {
				enemySpawnTimer = 4;
                    
                fox::Transform transform{ fox::vec2{fox::random::getReal() * 1280, fox::random::getReal() * 1024 }, 0, 2 };
                std::unique_ptr<Enemy> enemy = std::make_unique<Enemy>(transform, fox::Resources().Get<fox::Texture>("textures/tankbase_02.png", fox::GetEngine().GetRenderer()));
                enemy->dampening = 1.5f;
                enemy->speed = (fox::random::getReal() * 1000) + 500;
                enemy->tag = "enemy";                    

                m_scene->AddActor(std::move(enemy));
            }

			healthSpawnTimer -= dt;
            if (healthSpawnTimer <= 0) {
				healthSpawnTimer = 30;
                                       
                    fox::Transform transform{ fox::vec2{fox::random::getReal() * 1280, fox::random::getReal() * 1024 }, 0, 0.5 };
                    std::unique_ptr<Health> health = std::make_unique<Health>(transform, fox::Resources().Get<fox::Texture>("textures/heart.png", fox::GetEngine().GetRenderer()));
                    health->tag = "health";

                    m_scene->AddActor(std::move(health));
            }
            break;
        case SpaceGame::GameState::PlayerDead:
			gameStateTimer -= dt;
            if (gameStateTimer <= 0) {
                lives--;
                if (lives == 0) {
                    gameState = GameState::GameOver;
                    fox::GetEngine().GetAudio().PlaySound("game_over");
                    musicChannel->stop();
                }
                else {
                    m_scene->RemoveAllActors();
                    gameState = GameState::StartRound;
                }
            }
            break;
        case SpaceGame::GameState::GameOver:
            if (fox::GetEngine().GetInput().GetKeyPressed(SDL_SCANCODE_SPACE)) {
                gameState = GameState::StartGame;
            }
            break;

        default:
            break;
        }

        m_scene->Update(fox::GetEngine().GetTime().GetDeltaTime());
    }

    void SpaceGame::Shutdown() {
        
    }

    void SpaceGame::Draw(fox::Renderer& renderer) {
        if (gameState == GameState::Title) {
            titleText->Create(renderer, "ENGINE  ASTEROIDS", fox::vec3{ 1,0,0 });
            titleText->Draw(renderer, 125, 400);
		}

        if (gameState == GameState::GameOver) {
            titleText->Create(renderer, "GAME OVER", fox::vec3{ 1,0,0 });
            titleText->Draw(renderer, 400, 400);
		     
		}

        if (gameState == GameState::Game) {
            auto texture = fox::Resources().Get<fox::Texture>("Textures/space-was-cool.png", fox::GetEngine().GetRenderer());

            float screenW = (float)fox::GetEngine().GetRenderer().GetWidth();
            float screenH = (float)fox::GetEngine().GetRenderer().GetHeight();
            float texW = (float)texture->GetSize().x;
            float texH = (float)texture->GetSize().y;

            // Compute scale to fill the screen
            float scaleX = screenW / texW;
            float scaleY = screenH / texH;
            float finalScale = (scaleX > scaleY) ? scaleX : scaleY; // Cover entire screen

            // Draw centered with no rotation
            fox::GetEngine().GetRenderer().DrawTexture(texture.get(), screenW * 0.5f, screenH * 0.5f, 0, finalScale);


            scoreText->Create(renderer, "Score " + std::to_string(score), fox::vec3{ 1,1,1 });
            scoreText->Draw(renderer, 20, 20);
            
            livesText->Create(renderer, "Lives " + std::to_string(lives), fox::vec3{ 1,1,1 });
            livesText->Draw(renderer, renderer.GetWidth() - 200.0f, 20.0f);
        }

		fox::GetEngine().GetPS().Draw(fox::GetEngine().GetRenderer());

        m_scene->Draw(renderer);
    }

    void SpaceGame::OnPlayerDeath(){
        gameState = GameState::PlayerDead;
        fox::GetEngine().GetAudio().PlaySound("pdeath");
        gameStateTimer = 2;
    }