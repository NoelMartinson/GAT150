#include "AudioSystem.h"
#include "../Core/StringHelper.h"
#include "../Core/Logger.h"
#include <iostream>
#include <fmod_errors.h>
#include <algorithm>
#include <SDL3/SDL_error.h>
#include <sstream>

namespace fox {
	bool AudioSystem::CheckFMODResult(FMOD_RESULT result) {
		if (result != FMOD_OK) {
			Logger::Error("{}", FMOD_ErrorString(result));
			return false;
		}
		return true;
	}

	bool AudioSystem::Initialize() {
		FMOD_RESULT result = FMOD::System_Create(&audioSystem);
		if (!CheckFMODResult(result)) {
			return false;
		}

		void* extradriverdata = nullptr;
		result = audioSystem->init(32, FMOD_INIT_NORMAL, extradriverdata);
		if (!CheckFMODResult(result)) {
			return false;
		}

		return true;
	}
	void AudioSystem::Shutdown() {
		CheckFMODResult(audioSystem->release());
	}

	void AudioSystem::Update() {
		CheckFMODResult(audioSystem->update());
	}

	bool AudioSystem::AddSound(const std::string& filename, const std::string& name, bool loop)
	{
		std::string key = (name.empty()) ? filename : name;
		std::transform(key.begin(), key.end(), key.begin(), [](unsigned char c) { return std::tolower(c); });

		if (soundMap.find(key) != soundMap.end()) {
			Logger::Error("Audio system {} already exists", key);
			return false;
		}

		FMOD::Sound* sound = nullptr;
		FMOD_MODE mode = loop ? (FMOD_LOOP_NORMAL | FMOD_CREATESTREAM) : FMOD_DEFAULT;

		FMOD_RESULT result = audioSystem->createSound(filename.c_str(), mode, nullptr, &sound);
		if (!CheckFMODResult(result)) return false;

		soundMap[key] = sound;
		return true;
	}


	FMOD::Channel* AudioSystem::PlaySound(const std::string& name)
	{
		std::string key = name;
		std::transform(key.begin(), key.end(), key.begin(), [](unsigned char c) { return std::tolower(c); });

		if (soundMap.find(key) == soundMap.end()) {
			Logger::Error("Audio system {} doesn't exist", key);
			return nullptr;
		}

		FMOD::Channel* channel = nullptr;
		audioSystem->playSound(soundMap[key], 0, false, &channel);
		return channel;        
	}			
}