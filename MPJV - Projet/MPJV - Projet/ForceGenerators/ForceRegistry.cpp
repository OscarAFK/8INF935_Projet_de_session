#include "ForceRegistry.h"
#include <iostream>

void ForceRegistry::addEntry(ForceEntry entry)
{
	m_registry.push_back(entry);
}

void ForceRegistry::addEntry(Rigidbody* rg, ForceGenerator* forceGenerator)
{
	m_registry.push_back(ForceEntry(rg, forceGenerator));
}

void ForceRegistry::removeEntry(int index)
{
	m_registry.erase(m_registry.begin() + index);
}

void ForceRegistry::updateForce(float deltaTime)
{
	for (std::size_t i = 0; i < m_registry.size(); ++i) {
		m_registry[i].forceGenerator->UpdateForce(m_registry[i].rigidbody, deltaTime);
	}
}
