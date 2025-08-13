#pragma once  
#include "Renderer/Texture.h"
#include "../Math/Transform.h"  
#include "../Renderer/Model.h"  
#include <memory>  
#include <string>

namespace fox {  
	class Actor {  
	public:
		std::string name;
		std::string tag;

		vec2 velocity{ 0, 0 };
		float dampening{ 0.0f };

		bool destroyed{ false };
		float lifespan{ 0 };

		Transform transform;  
		class Scene* scene{ nullptr };
	public:  
		Actor() = default;  
		Actor(const fox::Transform& transform, res_t<Texture> texture) :
			transform(transform),  
			texture{ texture }  
		{}  

		virtual void Update(float dt);  
		virtual void Draw(class Renderer& renderer);  

		virtual void OnCollision(Actor* other) = 0;

		float GetRadius();

	protected:  
		res_t<Texture> texture;
		//std::shared_ptr<Model> model;
	};  
}