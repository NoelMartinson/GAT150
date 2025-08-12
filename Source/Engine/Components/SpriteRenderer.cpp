#include "EnginePCH.h"
#include "SpriteRenderer.h"
#include "Renderer/Renderer.h"
#include "Framework/Actor.h"

namespace fox {
	void SpriteRenderer::Update(float dt){
	}

    void SpriteRenderer::Draw(Renderer& renderer) {
        auto texture = Resources().Get<Texture>(textureName, renderer);
        if (texture) {
            renderer.DrawTexture(texture.get(), owner->transform.position.x, owner->transform.position.y);
        }
    }
}