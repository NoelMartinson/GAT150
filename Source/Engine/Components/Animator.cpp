#include "Animator.h"
#include "SpriteRenderer.h"
#include "Renderer/Renderer.h"
#include "Renderer/TextureAnimation.h"
#include "Engine.h"

namespace fox {
    FACTORY_REGISTER(Animator)

        void Animator::Start() {
        spriteRenderer = owner->GetComponent<SpriteRenderer>();
        if (!spriteRenderer) {
            Logger::Error("Animator missing sprite renderer.");
        }

        for (auto& animation : animations) {
            animation.second.textureAnimation = Resources().Get<TextureAnimation>(animation.second.textureAnimationName, GetEngine().GetRenderer());
            if (!animation.second.textureAnimation) {
                Logger::Warning("Could not load Animator texture animation {}", animation.second.textureAnimationName);
            } else {
                Logger::Info("Animator animation {}, textire {} loaded", animation.first, animation.second.textureAnimationName);
            }

        }

        auto it = animations.begin();
        std::string name = it->first;
        Play(name);

    }

    void Animator::Update(float dt) {
        if (paused || !currentAnimation.textureAnimation) return;

        frameTimer -= dt * speedMultiplier;
        if (frameTimer <= 0) {
            frameTimer = 1.0f / currentAnimation.textureAnimation->GetFPS();
            frame++;
            if (frame >= currentAnimation.textureAnimation->GetTotalFrames()) {
                if (currentAnimation.textureAnimation->GetTotalFrames()) {
                    frame = 0;
                }
                else {
                    frame = currentAnimation.textureAnimation->GetTotalFrames() - 1;
                }
            }

            if (spriteRenderer) {
                spriteRenderer->textureRect = currentAnimation.textureAnimation->GetFrameRect(frame);
            }
        }
    }

    void Animator::Play(const std::string& name, bool resetFrame) {
        if (equalsIgnoreCase(name, currentAnimationName)) return;

        auto it = animations.find(tolower(name));
        if (it == animations.end()) {
            Logger::Error("Animation does not exist in animation {}", name);
            return;
        }

        currentAnimationName = name;
        currentAnimation = it->second;

        if (resetFrame) frame = 0;
        frameTimer = 1.0f / currentAnimation.textureAnimation->GetFPS();

        if (spriteRenderer) {
            spriteRenderer->texture = currentAnimation.textureAnimation->GetTexture();
            spriteRenderer->textureRect = currentAnimation.textureAnimation->GetFrameRect(frame);
        }
    }

    void Animator::Read(const json::value_t& value) {
        Object::Read(value);

        JSON_READ(value, frame);

        if (JSON_HAS(value, animations) && JSON_GET(value, animations).IsArray()) {
            for (auto& animatorValue : JSON_GET(value, animations).GetArray()) {
                std::string name;
                std::string textureAnimationName;

                JSON_READ(animatorValue, name);

                JSON_READ_NAME(animatorValue, "texture_animation", textureAnimationName);

                TextureAnimInfo textureAnimInfo;
                textureAnimInfo.textureAnimationName = textureAnimationName;

                animations[tolower(name)] = textureAnimInfo;
            }
        }
    }
}
