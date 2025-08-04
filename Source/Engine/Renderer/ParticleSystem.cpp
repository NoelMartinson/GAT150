#include "ParticleSystem.h"

namespace fox {
	bool ParticleSystem::Initialize(int poolSize) {
		particles.resize(poolSize);

		return true;
	}

	void ParticleSystem::Shutdown() {
		particles.clear();
	}

	void ParticleSystem::Update(float dt) {
		for (auto& particle : particles) {
			if (particle.active) {
				particle.lifespan -= dt;
				particle.active = (particle.lifespan > 0);
				particle.position += particle.velocity * dt;
			}
		}
	}

	void ParticleSystem::Draw(class Renderer& renderer) {
		for (auto& particle : particles) {
			if (particle.active) {
				renderer.SetColor(particle.color.r, particle.color.g, particle.color.b);
				renderer.DrawPoint(particle.position.x, particle.position.y);
				
			}
		}
	}
	void ParticleSystem::AddParticle(const Particle& particle)
	{
		Particle* freeParticle = GetFreeParticle();
		if (freeParticle) {
			*freeParticle = particle;

			freeParticle->active = true;
		}
	}

	Particle* ParticleSystem::GetFreeParticle(){
		for(auto& particle : particles) {
			if (!particle.active == false) return &particle;
			
		}

		return nullptr;
	}
}