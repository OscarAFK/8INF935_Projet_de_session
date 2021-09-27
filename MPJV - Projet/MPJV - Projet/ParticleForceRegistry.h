#pragma once
#include <vector>
#include "ParticleForceGenerator.h"

class ParticleForceRegistry
{
private:
	struct ParticleForceEntry
	{
		Particle* particle;
		ParticleForceGenerator* forceGenerator;
	};

	using Registry = std::vector<ParticleForceEntry>;
	Registry m_registry;

public:
	void UpdateForce(float deltaTime);
};