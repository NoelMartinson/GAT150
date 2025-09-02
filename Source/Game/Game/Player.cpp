#include "Player.h"
#include "Engine.h"
#include "Rocket.h"
#include "SpaceGame.h"
#include "GameData.h"
#include "../GamePCH.h"

FACTORY_REGISTER(Player)

void Player::Start() {
    rigidBody = owner->GetComponent<fox::RigidBody>();
}

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
    
    owner->transform.rotation += (rotate * rotateRate) * dt;

    float thrust = 0;
	if (fox::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_W)) thrust = +1;

    fox::vec2 direction{ 1, 0 };
	fox::vec2 force = direction.Rotate(fox::math::degToRad(owner->transform.rotation)) * thrust * speed;

    auto rb = owner->GetComponent<fox::RigidBody>();
    if (rb) {
        rb->velocity += force * dt;
    }

	owner->transform.position.x = fox::math::wrap(owner->transform.position.x, 0.0f, (float)fox::GetEngine().GetRenderer().GetWidth());
    owner->transform.position.y = fox::math::wrap(owner->transform.position.y, 0.0f, (float)fox::GetEngine().GetRenderer().GetHeight());

    fireTimer -= dt;
    if (fox::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_SPACE) && fireTimer <= 0) {
        fireTimer = fireTime;
        fox::GetEngine().GetAudio().PlaySound("rocket");
       fox::Transform transform{owner->transform.position, owner->transform.rotation, 1.0f};
	   auto rocket = fox::Instantiate("rocket", transform);       
       rocket->tag = "player";
	   rocket->lifespan = 2.0f;
       
	   owner->scene->AddActor(std::move(rocket), true);
    }
}

void Player::OnCollision(fox::Actor* other)
{    
    if (other->tag == "health") {
        return;
    } 


    if (other->tag == "enemy") {
        owner->destroyed = true;
    	EVENT_NOTIFY("player_dead");
            
    }
}

void Player::Read(const fox::json::value_t& value){
    Object::Read(value);

    JSON_READ(value, speed);
    JSON_READ(value, rotateRate);
    JSON_READ(value, fireTime);
}
 