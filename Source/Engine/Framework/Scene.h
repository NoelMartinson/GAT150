#pragma once
#include "../Core/StringHelper.h"
#include <string>
#include <vector>
#include <memory>
#include <list>

namespace fox {
	class Actor;
	class Game;

	class Scene {
	public:
		Scene(Game* game) : game{ game } {}

		void Update(float dt);
		void Draw(class Renderer& renderer);

		void AddActor(std::unique_ptr<Actor> actor);
		void RemoveAllActors();

		template <typename T = Actor>
		T* GetActorByName(const std::string& name);

		template <typename T = Actor>
		std::vector<T*> GetActorsByTag(const std::string& tag);

		class Game* GetGame() const { return game; }

	private:
		class Game* game{ nullptr };
		std::list<std::unique_ptr<class Actor>> actors;
	};

	template<typename T>
	inline T* Scene::GetActorByName(const std::string& name)
	{
		for (auto& actor : actors) {
			if (fox::tolower(actor->name) == fox::tolower(name)) {
				T* object = dynamic_cast<T*>(actor.get());
				if (object) {
					return object;
				}
			}
		}

		return nullptr;
	}

	template<typename T>
	inline std::vector<T*> Scene::GetActorsByTag(const std::string& tag)
	{
		std::vector<T*> results;
		for (auto& actor : actors){
			if (tolower(actor->tag) == tolower(tag)){
				T* object = dynamic_cast<T*>(actor.get());
				if (object){
					results.push_back(object);
				}
			}
		} 

		return results;
	}
}