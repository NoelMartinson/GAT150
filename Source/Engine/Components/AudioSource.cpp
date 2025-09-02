#include "AudioSource.h"
#include "Audio/AudioClip.h"

namespace fox {
	FACTORY_REGISTER(AudioSource)

	void AudioSource::Update(float dt)	{
	}

	void AudioSource::Play() const	{
		auto audioClip = Resources().Get<AudioClip>(audioClipName, GetEngine().GetAudio());
		if (audioClip) {
			GetEngine().GetAudio().PlaySound(*audioClip);
		}
	}
}