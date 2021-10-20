#pragma once
#include "../Particle.h"

class ParticleForceGenerator
{
public :
	virtual void UpdateForce(Particle* particle, float deltaTime) = 0;
};