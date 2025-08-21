#include "Scene.h"
#include "../Renderer/Renderer.h"
#include "Components/ColliderComponent.h"

namespace fox {
	void Scene::Update(float dt){ 
		for (auto& actor : actors) {
			if (actor->active) {
				actor->Update(dt);
			}
		}

		for (auto iter = actors.begin(); iter != actors.end();) {
			if ((*iter)->destroyed) {
				iter = actors.erase(iter);
			} else {
				iter++;
			}
		}

		for (auto& actorA : actors) {
			for (auto& actorB : actors) {
				if (actorA == actorB || (actorA->destroyed || actorA->destroyed)) continue;

				auto colliderA = actorA->GetComponent<ColliderComponent>();
				auto colliderB = actorB->GetComponent<ColliderComponent>();

				if (!colliderA || !colliderB) continue;

				if (colliderA->CheckCollision(*colliderB)) {
					actorA->OnCollision(actorB.get());
					actorB->OnCollision(actorA.get());
				}			
			}
		}
	};

	void Scene::Draw(Renderer& renderer) {
		for (auto& actor : actors) {
			if (actor->active) {
				actor->Draw(renderer);
			}
		}
	}
	void Scene::AddActor(std::unique_ptr<class Actor> actor){
		actor->scene = this;
		actors.push_back(std::move(actor));
	}
	void Scene::RemoveAllActors(){
		actors.clear();
	}

	void Scene::Read(const json::value_t& value){
		if (JSON_HAS(value, name)) {
			for (auto& actorValue : JSON_GET(value, actors).GetArray()) {

				auto actor = Factory::Instance().Create<Actor>("Actor");
				actor->Read(actorValue);

				AddActor(std::move(actor));
			}
		}	
	}
}