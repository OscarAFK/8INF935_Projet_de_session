#pragma once
#include "ParticleContact.h"

class ParticleContactResolver
{
protected:
	unsigned int m_iteration;

public:

	ParticleContactResolver() = default;

	void resolveContacts(ParticleContact* contactArray,
						unsigned int numContact,
						float duration);
};