#include "ParticleContact.h"

class ParticleContactResolver
{
protected:
	unsigned int m_iteration;

public:

	void resolveContacts(ParticleContact* contactArray,
						unsigned int numContact,
						float duration);
};