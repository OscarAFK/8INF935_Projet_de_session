#pragma once
#include "ParticleContact.h"
#include <vector>

class ParticleContactGenerator
{
public:
	virtual unsigned int addContact(ParticleContact* contact, unsigned int  limit) = 0;
};