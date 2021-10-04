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
		if (m_registry[i].particle != nullptr)
		{
			std::cout << "particle not null";
		}
		if (m_registry[i].forceGenerator != nullptr)
		{
			std::cout << "forceGenerator not null";
		}
		std::cout << m_registry[i].particle->to_string();
		m_registry[i].forceGenerator->UpdateForce(m_registry[i].particle, deltaTime);//0xC0000005 : Violation d'accès lors de la lecture de l'emplacement 0x0000000000000008.
	}
}

std::string ParticleForceRegistry::to_string()
{
	std::string result;
	for (int i = 0; i < m_registry.size(); i++)
	{
		result += "Entry #" + std::to_string(i) + " :\n";
		result += m_registry[i].particle->to_string();
		result += m_registry[i].forceGenerator->to_string() + "\n";
	}
	return result;
}
