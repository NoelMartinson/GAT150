#pragma once
#include <fmod.hpp>
#include <fmod_errors.h>
#include <iostream>
#include <map>

namespace fox {
	class AudioSystem {
	public:
		AudioSystem() = default;

		bool Initialize();
		void Shutdown();

		void Update();

		bool AddSound(const std::string& filename, const std::string& name, bool loop);
		FMOD::Channel* PlaySound(const std::string& name);

	private:
		bool CheckFMODResult(FMOD_RESULT result);

	private:
		FMOD::System* audioSystem = nullptr;
		std::map<std::string, FMOD::Sound*> soundMap;
	};
}