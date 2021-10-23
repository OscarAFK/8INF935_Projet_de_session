#pragma once
#include "ParticleContact.h"
#include <vector>

class ParticleContactResolver
{
protected:
	unsigned int m_iteration;

public:

	ParticleContactResolver() = default;

	void resolveContacts(std::vector<ParticleContact*> contactArray,
						unsigned int numContact,
						float duration);
};