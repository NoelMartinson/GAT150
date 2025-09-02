#pragma once
#include "Framework/Component.h"

namespace fox{
	class AudioSource : public Component {
	public:
		std::string audioClipName;

	public:			
		CLASS_PROTOTYPE(AudioSource)

		void Update(float dt) override;
		void Play() const;
	};
}