#include "../GamePCH.h"
#include "Health.h"
#include "Engine.h"
#include "Player.h"

FACTORY_REGISTER(Health)

void Health::Initialize()
{
    fox::GetEngine().GetAudio().AddSound("enemy_death.wav", "edeath", false);
	fox::GetEngine().GetAudio().AddSound("health.wav", "health", false);
}

void Health::Update(float dt)
{
}

void Health::OnCollision(fox::Actor* other)
{
    if (other->tag == "player" && other->name == "player") {
        owner->destroyed = true;
        owner->scene->GetGame()->AddLives(1);
        fox::GetEngine().GetAudio().PlaySound("health");

    }

    if (other->tag == "player" && other->name == "rocket") {
        owner->destroyed = true;
        fox::GetEngine().GetAudio().PlaySound("edeath");
    }
}

void Health::Read(const fox::json::value_t& value){
	Object::Read(value);
}
