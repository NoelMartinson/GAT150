#include "Engine.h"
#include "Renderer/Renderer.h"
#include "Input/InputSystem.h"
#include "Audio/AudioSystem.h"
#include "Renderer/ParticleSystem.h"

namespace fox {

	bool Engine::Initialize() {
		m_renderer = std::make_unique<fox::Renderer>();
		m_renderer->Initialize();
		m_renderer->CreateWindow("Fox Engine", 1280, 1024, false);

		m_input = std::make_unique<fox::InputSystem>();
		m_input->Initialize();

		m_audio = std::make_unique<fox::AudioSystem>();
		m_audio->Initialize();
		FMOD::Sound* sound = nullptr;

		m_particleSystem = std::make_unique<fox::ParticleSystem>();
		m_particleSystem->Initialize(5000);

		m_physics = std::make_unique<Physics>();
		m_physics->Initialize();
		Physics::setPixelsPerUnit(32.0f);

		return true;
	}

	void Engine::Shutdown() {
		Resources().Clear();
		Factory::Instance().RemoveAll();
		EventManager::Instance().RemoveAll();

		m_physics->Shutdown();
		m_particleSystem->Shutdown();
		m_audio->Shutdown();
		m_input->Shutdown();
		m_renderer->Shutdown();
	}

	void Engine::Update() {
		m_time.Tick();
		m_input->Update();
		m_audio->Update();
		m_particleSystem->Update(m_time.GetDeltaTime());
		m_physics->Update(m_time.GetDeltaTime());
	}
	void Engine::Draw(){

	}
}