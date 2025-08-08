#include "Player.h"
#include "Engine.h"
#include "Rocket.h"
#include "SpaceGame.h"
#include "Renderer/Renderer.h" 
#include "Renderer/ParticleSystem.h"
#include "Core/Random.h"
#include "Renderer/Model.h"
#include "Input/InputSystem.h"
#include "Framework/Scene.h"    
#include "GameData.h"
#include "Audio/AudioSystem.h"

#include <iostream>

void Player::Update(float dt){

    /*fox::Particle particle;
    particle.position = transform.position;
    particle.velocity = fox::vec2{ fox::random::getReal(200.0f), fox::random::getReal(200.0f)};
	particle.color = fox::vec3{ 1, 1, 1 };
	particle.lifespan = 2.0f;
	fox::GetEngine().GetPS().AddParticle(particle);*/

   
    float rotate = 0;
    if (fox::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_A)) rotate = -1;
    if (fox::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_D)) rotate = +1;
    
	transform.rotation += (rotate * rotateRate) * dt;

    float thrust = 0;
	if (fox::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_W)) thrust = +1;

    fox::vec2 direction{ 1, 0 };
	fox::vec2 force = direction.Rotate(fox::math::degToRad(transform.rotation)) * thrust * speed;
    velocity += force * dt;

	transform.position.x = fox::math::wrap(transform.position.x, 0.0f, (float)fox::GetEngine().GetRenderer().GetWidth());
    transform.position.y = fox::math::wrap(transform.position.y, 0.0f, (float)fox::GetEngine().GetRenderer().GetHeight());

    fireTimer -= dt;
    if (fox::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_SPACE) && fireTimer <= 0) {
        fireTimer = fireTime;
        fox::GetEngine().GetAudio().PlaySound("rocket");
        
        std::shared_ptr<fox::Model>model = std::make_shared < fox::Model>(GameData::rocketPoints, fox::vec3{ 1,0,1 });
        fox::Transform transform{this->transform.position, this->transform.rotation, 2.0f};
        auto rocket = std::make_unique<Rocket>(transform, model);
        rocket->speed = 1500.0f;
        rocket->lifespan = 1.5f;
        rocket->tag = "player";
        rocket->name = "rocket";


        scene->AddActor(std::move(rocket));
    }

	Actor::Update(dt);
}

void Player::OnCollision(Actor* other)
{
    
    if (other->tag == "health") {
        return;
    } 

    if (other->tag == "enemy") {
        destroyed = true;
        dynamic_cast<SpaceGame*>(scene->GetGame())->OnPlayerDeath();
    }
}
 