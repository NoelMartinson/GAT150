#include "Actor.h"
#include "Components/RendererComponent.h"
#include "Renderer/Renderer.h"

namespace fox {
	void fox::Actor::Update(float dt) {
		if (destroyed) return;



		if (lifespan > 0) {
			lifespan -= dt;
			if(lifespan <= 0) {
				destroyed = true;
				return;
			}
		}

		for (auto& component : components) {
			if (component->active) {
				component->Update(dt);
			}
		}		
	}
	 
	void fox::Actor::Draw(Renderer& renderer) {
		if (destroyed) return;

		for (auto& component : components) {
			if (component->active) {
				auto rendererComponent = dynamic_cast<RendererComponent*>(component.get());
				if (rendererComponent) {
					rendererComponent->Draw(renderer);
				}
			}
		}
	}

	void Actor::AddComponent(std::unique_ptr<class Component> component)
	{
		component->owner = this;
		components.push_back(std::move(component));
	}
}