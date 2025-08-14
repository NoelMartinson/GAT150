#include "AudioSource.h"
#include "Audio/AudioClip.h"

namespace fox {
	void AudioSource::Update(float dt)	{
	}

	void fox::AudioSource::Play()	{
		auto audioClip = Resources().Get<AudioClip>(audioClipName, GetEngine().GetAudio());
		if (audioClip) {
			GetEngine().GetAudio().PlaySound(*audioClip);
		}
	}
}