#include "Actor.h"
#include "../Renderer/Model.h"

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
		model->Draw(renderer, transform);
	}

	float Actor::GetRadius()
	{
		return (model) ? model->GetRadius() * transform.scale: 0;
	}
}