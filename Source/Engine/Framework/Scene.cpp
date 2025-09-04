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

		std::erase_if(actors, [](auto& actor) {
			return (actor->destroyed);
		});		

		/*for (auto& actorA : actors) {
			for (auto& actorB : actors) {

				continue;

				if (actorA == actorB || (actorA->destroyed || actorB->destroyed)) continue;

				auto colliderA = actorA->GetComponent<ColliderComponent>();
				auto colliderB = actorB->GetComponent<ColliderComponent>();

				if (!colliderA || !colliderB) continue;

				if (colliderA->CheckCollision(*colliderB)) {
					actorA->OnCollision(actorB.get());
					actorB->OnCollision(actorA.get());
				}			
			}
		}*/
	};

	void Scene::Draw(Renderer& renderer) {
		for (auto& actor : actors) {
			if (actor->active) {
				actor->Draw(renderer);
			}
		}
	}
	void Scene::AddActor(std::unique_ptr<class Actor> actor, bool start) {
		actor->scene = this;
		if (start) actor->Start();
		actors.push_back(std::move(actor));
	}

	void Scene::RemoveAllActors(bool force){
		for (auto iter = actors.begin(); iter != actors.end(); ) {
			if (!(*iter)->persistant || force) {
				iter = actors.erase(iter);
			}
			else {
				iter++;
			}
		}
	}

	bool Scene::Load(const std::string& sceneName) {
		fox::json::document_t document;
		if (!fox::json::Load(sceneName, document)) {
			//Logger::Error("Failed to load scene: " + sceneName);
			return false;
		}

		Read(document);

		for(auto& actor : actors) {
			actor->Start();
		}

		return true;
	}

	void Scene::Read(const json::value_t& value){
		if (JSON_HAS(value, prototypes)) {
			for (auto& actorValue : JSON_GET(value, prototypes).GetArray()) {

				auto actor = Factory::Instance().Create("Actor");
				actor->Read(actorValue);

				std::string name = actor->name;
				Factory::Instance().RegisterPrototype(name, std::move(actor));
			}
		}	

		if (JSON_HAS(value, actors)) {
			for (auto& actorValue : JSON_GET(value, actors).GetArray()) {

				auto actor = Factory::Instance().Create<Actor>("Actor");
				actor->Read(actorValue);

				AddActor(std::move(actor), false);
			}
		}
	}
}