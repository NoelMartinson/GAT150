#include "Actor.h"
#include "Renderer/Renderer.h"

namespace fox {
	void fox::Actor::Update(float dt) {
		if (destroyed) return;

		if (lifespan != 0) {
			lifespan -= dt;
			destroyed = lifespan <= 0;
		}

		transform.position += velocity * dt;
		velocity *= (1.0f / (1.0f + dampening * dt));
	}

	void fox::Actor::Draw(Renderer& renderer) {
		if (destroyed) return;
		renderer.DrawTexture(texture.get() , transform.position.x, transform.position.y, transform.rotation, transform.scale);
	}

	float Actor::GetRadius()
	{
		return (texture) ? (texture->GetSize().Length() * 0.5f) * transform.scale * 0.9f : 0;
	}
}