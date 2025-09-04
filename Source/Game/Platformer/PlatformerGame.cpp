#include "PlatformerGame.h"
#include "Engine.h"


bool PlatformerGame::Initialize(){
	/*OBSERVER_ADD(player_dead);
	OBSERVER_ADD(add_points);*/

	m_scene = std::make_unique<fox::Scene>(this);
	m_scene->Load("Scenes/prototype.json");
	m_scene->Load("Scenes/level.json");

	return false;
}

void PlatformerGame::Shutdown(){
}

void PlatformerGame::Update(float dt){
	switch (gameState)
	{
	case PlatformerGame::GameState::Initalize:
		gameState = GameState::StartRound;
		break;
	case PlatformerGame::GameState::Title:
		break;
	case PlatformerGame::GameState::StartGame:
		break;
	case PlatformerGame::GameState::StartRound:
		SpawnPlayer();
		SpawnEnemy();
		gameState = GameState::Game;
		break;
	case PlatformerGame::GameState::Game:
		break;
	case PlatformerGame::GameState::PlayerDead:
		break;
	case PlatformerGame::GameState::GameOver:
		break;
	default:
		break;
	}

	m_scene->Update(fox::GetEngine().GetTime().GetDeltaTime());
}

void PlatformerGame::Draw(fox::Renderer& renderer){
	m_scene->Draw(renderer);
	fox::GetEngine().GetPS().Draw(renderer);
}

void PlatformerGame::OnPlayerDeath() {

}

void PlatformerGame::OnNotify(const fox::Event& event){
}

void PlatformerGame::SpawnPlayer(){
	auto player = fox::Instantiate("platformplayer");
	//player->transform.position = fox::vec2{ fox::random::getReal(0.0f, 1280.0f), fox::random::getReal(0.0f, 100.0f)};
	m_scene->AddActor(std::move(player));
}

void PlatformerGame::SpawnEnemy() {
	auto enemy = fox::Instantiate("platformenemy");
	//player->transform.position = fox::vec2{ fox::random::getReal(0.0f, 1280.0f), fox::random::getReal(0.0f, 100.0f)};
	m_scene->AddActor(std::move(enemy));
}


