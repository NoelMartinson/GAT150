#include "SpriteRenderer.h"
#include "Renderer/Renderer.h"
#include "Framework/Actor.h"

namespace fox {
	void SpriteRenderer::Update(float dt){
	}

    void SpriteRenderer::Draw(Renderer& renderer) {   
        auto texture = Resources().Get<Texture>(textureName, renderer).get();

        if (texture) {
            renderer.DrawTexture(*texture,
                owner->transform.position.x,
                owner->transform.position.y,
                owner->transform.rotation,
                owner->transform.scale);
        }
    }
}