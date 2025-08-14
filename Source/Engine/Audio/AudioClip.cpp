#include "AudioClip.h"
#include "AudioSystem.h"

namespace fox {
	AudioClip::~AudioClip() {
		if (sound) sound->release();
	}

	bool AudioClip::Load(const std::string& filename, AudioSystem& audiosystem) {
		FMOD_RESULT result = audiosystem.audioSystem->createSound(filename.c_str(), FMOD_DEFAULT, 0, &sound);
		if (!AudioSystem::CheckFMODResult(result)) return false;

		return true;
	}
}