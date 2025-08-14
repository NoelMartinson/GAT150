#pragma once  
#include "Renderer/Texture.h"
#include "Object.h"
#include "Component.h"
#include "Math/Transform.h"  
#include "Renderer/Mesh.h"  
#include <memory>  
#include <string>
#include <vector>

namespace fox {  
	class Actor : public Object {  
	public:
		std::string tag;

		bool destroyed{ false };
		float lifespan{ 0 };

		Transform transform;  
		class Scene* scene{ nullptr };
	public:  
		Actor() = default;  
		Actor(const fox::Transform& transform) :
			transform(transform)
		{}  

		virtual void Update(float dt);  
		virtual void Draw(class Renderer& renderer);  

		virtual void OnCollision(Actor* other) = 0;

		//
		void AddComponent(std::unique_ptr<Component> component);

		template<typename T>
		T* GetComponent();

		template<typename T>
		std::vector<T*> GetComponents();



	protected:  
		std::vector<std::unique_ptr<Component>> components;
	};  

	template<typename T>
	inline T* Actor::GetComponent()
	{
		for (auto& component : components) {
			auto result = dynamic_cast<T*>(component.get());
			if (result) {
				return result;
			}
		}
		return nullptr;
	}

	template<typename T>
	inline std::vector<T*> Actor::GetComponents()
	{
		std::vector<T*> results;

		for (auto& component : components) {
			auto result = dynamic_cast<T*>(component.get());
			if (result) {
				results.push_back(result);
			}
		}
		return results;
	}
}