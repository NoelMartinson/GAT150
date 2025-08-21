#include "Actor.h"
#include "Components/RendererComponent.h"
#include "Renderer/Renderer.h"

namespace fox {
	FACTORY_REGISTER(Actor)

	void Actor::Update(float dt) {
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
	 
	void Actor::Draw(Renderer& renderer) {
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

	void Actor::AddComponent(std::unique_ptr<class Component> component){
		component->owner = this;
		components.push_back(std::move(component));
	}
	void Actor::Read(const json::value_t& value){
		Object::Read(value);

		JSON_READ(value, tag);
		JSON_READ(value, lifespan);

		if (JSON_HAS(value, transform)) transform.Read(JSON_GET(value, transform));

		if (JSON_HAS(value, componenets)) {
			for (auto& comonentValue : JSON_GET(value, components).GetArray()) {

				std::string type;
				JSON_READ(comonentValue, type);

				auto component = Factory::Instance().Create<Component>(type);
				component->Read(comonentValue);

				AddComponent(std::move(component));
			}
		}
	}
}