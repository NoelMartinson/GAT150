#pragma once
#include "Resource/Resource.h"

namespace fox {
	class AudioClip : public Resource {
	public:
		AudioClip() = default;
		~AudioClip();

		bool Load(const std::string& filename, AudioSystem& audiosystem);
	private:
		friend class AudioSystem;

		FMOD::Sound* sound{ nullptr };
	};
}