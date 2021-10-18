#include "ParticleContact.h"

class ParticleContactGenerator
{
public:
	virtual unsigned int addContact(ParticleContact* contact, unsigned int  limit) = 0;
};