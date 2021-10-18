#include "ParticleContact.h"

class ParticleContactGenerators
{
public:
	virtual unsigned int addContact(ParticleContact* contact, unsigned int  limit) = 0;
};