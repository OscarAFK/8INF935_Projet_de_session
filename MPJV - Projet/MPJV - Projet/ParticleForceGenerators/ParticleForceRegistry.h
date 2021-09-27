#pragma once
#include <vector>
#include "ParticleForceGenerator.h"

class ParticleForceRegistry
{
private:
	struct ParticleForceEntry
	{
		ParticleForceEntry(Particle* p, ParticleForceGenerator* pfg) : particle{ p }, forceGenerator{ pfg }{};
		Particle* particle;
		ParticleForceGenerator* forceGenerator;
	};

	using Registry = std::vector<ParticleForceEntry>;
	Registry m_registry;

public:
	Registry getRegistry()
	{
		return m_registry;
	}
	void addEntry(ParticleForceEntry entry);
	void addEntry(Particle* particle, ParticleForceGenerator* forceGenerator);
	void removeEntry(int index);
	void updateForce(float deltaTime);
};