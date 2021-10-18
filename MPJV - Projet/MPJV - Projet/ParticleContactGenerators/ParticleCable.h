#pragma once
#include "ParticleLink.h"

class ParticleCable : public ParticleLink
{
public:
	// A contact will be generated if the distance
	//between particles is larger than maxLength
	float maxLength;

	//bounciness of the cable
	float restitution;

	unsigned int addContact(ParticleContact* contact, unsigned int limit) const;
};