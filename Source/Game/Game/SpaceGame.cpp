#include "../GamePCH.h"
#include "SpaceGame.h"
#include "Player.h"
#include "Enemy.h"
#include "Health.h"
#include "GameData.h"

bool SpaceGame::Initialize() {
    OBSERVER_ADD(player_dead);
    OBSERVER_ADD(add_points);      	

    m_scene = std::make_unique<fox::Scene>(this);
	m_scene->Load("scene.json");

    fox::GetEngine().GetAudio().AddSound("music.wav", "music", true);
    
    fox::GetEngine().GetAudio().AddSound("enemy_death.wav", "edeath", false);
    fox::GetEngine().GetAudio().AddSound("player_death.wav", "pdeath", false);
    fox::GetEngine().GetAudio().AddSound("game_over.wav", "game_over", false);
    fox::GetEngine().GetAudio().AddSound("health.wav", "health", false);
	fox::GetEngine().GetAudio().AddSound("rocket.wav", "rocket", false);


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
		m_scene->RemoveAllActors();
            
        auto player = fox::Instantiate("player");
        m_scene->AddActor(std::move(player));

		gameState = SpaceGame::GameState::Game;
    }
    break;

    case SpaceGame::GameState::Game:
        enemySpawnTimer -= dt;
        if (enemySpawnTimer <= 0) {
            enemySpawnTimer = 4;
            SpawnEnemy();
        }

        healthSpawnTimer -= dt;
        if (healthSpawnTimer <= 0) {
            healthSpawnTimer = 30;

			SpawnHealth();
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
    m_scene->Draw(renderer);

    if (gameState == GameState::Title) {
        titleText->Create(renderer, "ENGINE  ASTEROIDS", fox::vec3{ 1,0,0 });
        titleText->Draw(renderer, 125, 400);
    }

    if (gameState == GameState::GameOver) {
        titleText->Create(renderer, "GAME OVER", fox::vec3{ 1,0,0 });
        titleText->Draw(renderer, 400, 400);

    }

    if (gameState == GameState::Game) {
        /*auto texture = fox::Resources().Get<fox::Texture>("Textures/space-was-cool.png", fox::GetEngine().GetRenderer());

        float screenW = (float)fox::GetEngine().GetRenderer().GetWidth();
        float screenH = (float)fox::GetEngine().GetRenderer().GetHeight();
        float texW = (float)texture->GetSize().x;
        float texH = (float)texture->GetSize().y;


        float scaleX = screenW / texW;
        float scaleY = screenH / texH;
        float finalScale = (scaleX > scaleY) ? scaleX : scaleY;*/

        //fox::GetEngine().GetRenderer().DrawTexture(*texture, screenW * 0.5f, screenH * 0.5f, 0, finalScale);

        scoreText->Create(renderer, "Score " + std::to_string(score), fox::vec3{ 1,1,1 });
        scoreText->Draw(renderer, 20, 20);

        livesText->Create(renderer, "Lives " + std::to_string(lives), fox::vec3{ 1,1,1 });
        livesText->Draw(renderer, renderer.GetWidth() - 200.0f, 20.0f);
    }

    fox::GetEngine().GetPS().Draw(fox::GetEngine().GetRenderer());    
}

void SpaceGame::OnPlayerDeath() {
    gameState = GameState::PlayerDead;
    fox::GetEngine().GetAudio().PlaySound("pdeath");

    gameStateTimer = 2;
}

void SpaceGame::OnNotify(const fox::Event& event){
    if (fox::equalsIgnoreCase(event.id, "player_dead")) {
        OnPlayerDeath();
    }
    else if (fox::equalsIgnoreCase(event.id, "add_points")) {
		AddPoints(std::get<int>(event.data));
	}
}

void SpaceGame::SpawnEnemy() {
    fox::Actor* player = m_scene->GetActorByName<fox::Actor>("player");
    if (player) {
        fox::vec2 position = player->transform.position + fox::vec2{
            fox::random::getReal(200.0f, 500.0f),
            fox::random::getReal(200.0f, 500.0f)
        };

        fox::Transform transform{ position, fox::random::getReal(0.0f, 360.0f), 2.0f };

        auto enemy = fox::Instantiate("enemy", transform);
        m_scene->AddActor(std::move(enemy));
    }
}

void SpaceGame::SpawnHealth(){
    fox::Actor* player = m_scene->GetActorByName<fox::Actor>("player");
    if (player) {
        fox::vec2 position = player->transform.position + fox::vec2{
            fox::random::getReal(200.0f, 500.0f),
            fox::random::getReal(200.0f, 500.0f)
        };

        fox::Transform transform{ position, fox::random::getReal(0.0f, 360.0f), 0.2f };

        auto health = fox::Instantiate("health", transform);
        m_scene->AddActor(std::move(health));
    }
}


    