#pragma once
#include "ParticleLink.h"

class ParticleRod : public ParticleLink
{
	// A contact will be generated if the distance
	//between particles is not equal to the length
	float length;

	unsigned int addContact(ParticleContact* contact, unsigned int limit) const;
};