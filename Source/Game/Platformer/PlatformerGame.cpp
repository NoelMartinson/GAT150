#include "PlatformerGame.h"
#include "Engine.h"
#include "../GamePCH.h"


bool PlatformerGame::Initialize(){
	
	OBSERVER_ADD(add_points);
	OBSERVER_ADD(player_hit);

	fox::GetEngine().GetAudio().AddSound("Hit.wav", "hitE", false);
	fox::GetEngine().GetAudio().AddSound("Hit1.wav", "hitP", false);
	fox::GetEngine().GetAudio().AddSound("Pickup5.wav", "coin", false);

	/*musicChannel = fox::GetEngine().GetAudio().PlaySound("music");
	musicChannel->setVolume(0.5f);*/

	m_scene = std::make_unique<fox::Scene>(this);
	m_scene->Load("Scenes/prototype.json");
	m_scene->Load("Scenes/level.json");


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

void PlatformerGame::Shutdown(){
}

void PlatformerGame::Update(float dt) {
	switch (gameState) {
	case GameState::Initalize:
		gameState = GameState::StartRound;
		break;
	case GameState::Title:
		break;
	case GameState::StartGame:
		score = 0;
		lives = 3;
		gameState = GameState::StartRound;
		break;
	case GameState::StartRound:
		SpawnPlayer();
		SpawnEnemy();
		score = 0;
		lives = 3;
		gameState = GameState::Game;
		break;
	case GameState::Game:
		healthSpawnTimer -= dt;
		if (healthSpawnTimer <= 0) {
			healthSpawnTimer = 5;
			SpawnPickup();
		}
		break;
	case GameState::PlayerDead:
		gameStateTimer -= dt;
		if (lives == 0) {
			gameState = GameState::GameOver;
		}		
		break;
	case GameState::GameOver:
		
		return;
	}

	// only update scene if not GameOver
	m_scene->Update(fox::GetEngine().GetTime().GetDeltaTime());
}



void PlatformerGame::Draw(fox::Renderer& renderer) {
	m_scene->Draw(renderer);
	fox::GetEngine().GetPS().Draw(renderer);

	scoreText->Create(renderer, "Score " + std::to_string(score), fox::vec3{ 1,1,1 });
	scoreText->Draw(renderer, 20, 20);

	livesText->Create(renderer, "Lives " + std::to_string(lives), fox::vec3{ 1,1,1 });
	livesText->Draw(renderer, renderer.GetWidth() - 200.0f, 20.0f);

	if (gameState == GameState::GameOver) {
		auto font = std::make_shared<fox::Font>();
		font->Load("ArcadeClassic.ttf", 72.0f);
		fox::Text gameOverText(font);
		gameOverText.Create(renderer, "GAME OVER", fox::vec3{ 1,0,0 });
		gameOverText.Draw(renderer, renderer.GetWidth() / 2 - 200, renderer.GetHeight() / 2 - 50);
	}
}


void PlatformerGame::OnPlayerDeath() {

}

void PlatformerGame::OnNotify(const fox::Event& event) {
	if (fox::equalsIgnoreCase(event.id, "add_points")) {
		AddPoints(std::get<int>(event.data));
	}
	else if (fox::equalsIgnoreCase(event.id, "player_hit")) {
		lives--;

		if (lives <= 0) {
			gameState = GameState::GameOver;
		}
		else {
			gameState = GameState::PlayerDead;
			gameStateTimer = 2.0f;
		}
	}
}


void PlatformerGame::SpawnPlayer(){
	auto player = fox::Instantiate("platformplayer");
	//player->transform.position = fox::vec2{ fox::random::getReal(0.0f, 1280.0f), fox::random::getReal(0.0f, 100.0f)};
	m_scene->AddActor(std::move(player));
}

void PlatformerGame::SpawnEnemy() {
	auto enemy = fox::Instantiate("bat");
	//player->transform.position = fox::vec2{ fox::random::getReal(0.0f, 1280.0f), fox::random::getReal(0.0f, 100.0f)};
	m_scene->AddActor(std::move(enemy));
}

void PlatformerGame::SpawnPickup(){
	auto pickup = fox::Instantiate("coin");
	pickup->transform.position = fox::vec2{ fox::random::getReal(50.0f, 1200.0f), fox::random::getReal(100.0f, 2000.0f) };
	m_scene->AddActor(std::move(pickup));
}


