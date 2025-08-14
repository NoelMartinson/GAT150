#include "../GamePCH.h"
#include "Health.h"
#include "Engine.h"
#include "Player.h"

void Health::Initialize()
{
    fox::GetEngine().GetAudio().AddSound("enemy_death.wav", "edeath", false);
	fox::GetEngine().GetAudio().AddSound("health.wav", "health", false);
}

void Health::Update(float dt)
{
}

void Health::OnCollision(Actor* other)
{
    if (other->tag == "player" && other->name == "player") {
        destroyed = true;
        scene->GetGame()->AddLives(1);
        fox::GetEngine().GetAudio().PlaySound("health");

    }

    if (other->tag == "player" && other->name == "rocket") {
        destroyed = true;
        fox::GetEngine().GetAudio().PlaySound("edeath");
    }
}
