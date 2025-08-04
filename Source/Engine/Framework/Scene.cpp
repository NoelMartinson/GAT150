#include "Scene.h"
#include "Actor.h"
#include "../Renderer/Renderer.h"
#include "../Core/StringHelper.h"

namespace fox {
	void Scene::Update(float dt){
		for (auto& actor : actors) {
			actor->Update(dt);
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

				float distance = (actorA->transform.position - actorB->transform.position).Length();
				if (distance <= actorA->GetRadius() + actorB->GetRadius()) {
					actorA->OnCollision(actorB.get());
					actorB->OnCollision(actorA.get());
				}
			}
		}
	};

	void Scene::Draw(Renderer& renderer) {
		for (auto& actor : actors) {
			actor->Draw(renderer);
		}
	}
	void Scene::AddActor(std::unique_ptr<class Actor> actor)
	{
		actor->scene = this;
		actors.push_back(std::move(actor));
	}
	void Scene::RemoveAllActors(){
		actors.clear();
	}
}