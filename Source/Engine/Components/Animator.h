#pragma once
#include "Framework/Component.h"
#include "Renderer/TextureAnimation.h"

namespace fox {
	class Animator : public Component {
	public:
		struct TextureAnimInfo {
			std::string textureAnimationName;
			res_t<TextureAnimation> textureAnimation;
		};

		int frame = 0;
		float speedMultiplier{ 1 };
	public:
		CLASS_PROTOTYPE(Animator)

		void Start() override;
		void Update(float dt) override;

		void Play(const std::string& name, bool resetFrame = true);
		void Pause(bool pause) { paused = pause; }
		bool IsPaused() const { return paused; }

		const std::string& GetCurrentAnimation() const { return currentAnimationName; }

		void Read(const json::value_t& value) override;

	private:
		float frameTimer = 0;
		bool paused = false;

		std::string currentAnimationName;
		TextureAnimInfo currentAnimation;

		std::map<std::string, TextureAnimInfo> animations;
		class SpriteRenderer* spriteRenderer{ nullptr };
	};
}