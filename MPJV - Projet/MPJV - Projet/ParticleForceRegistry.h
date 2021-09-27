#pragma once
#include <vector>
#include "ParticleForceGenerator.h"

class ParticleForceRegistry
{
private:
	struct ParticleForceENtry
	{
		Particle* particle;
		ParticleForceGenerator* forceGenerator;
	};

	using Registry = std::vector<ParticleForceGenerator>;
	Registry m_registry;

public:
	void UpdateForce(float deltaTime);
};