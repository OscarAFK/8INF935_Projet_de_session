#include "ParticleForceRegistry.h"
#include <iostream>

void ParticleForceRegistry::addEntry(ParticleForceEntry entry)
{
	m_registry.push_back(entry);
}

void ParticleForceRegistry::addEntry(Particle* particle, ParticleForceGenerator* forceGenerator)
{
	m_registry.push_back(ParticleForceEntry(particle, forceGenerator));
}

void ParticleForceRegistry::removeEntry(int index)
{
	m_registry.erase(m_registry.begin() + index);
}

void ParticleForceRegistry::updateForce(float deltaTime)
{
	for (std::size_t i = 0; i < m_registry.size(); ++i) {
		m_registry[i].forceGenerator->UpdateForce(m_registry[i].particle, deltaTime);//0xC0000005 : Violation d'accès lors de la lecture de l'emplacement 0x0000000000000008.
	}
}
