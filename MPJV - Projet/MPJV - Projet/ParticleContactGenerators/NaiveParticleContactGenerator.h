#pragma once
#include "ParticleContactGenerator.h"
#include <vector>
#include <algorithm>

class NaiveParticleContactGenerator : ParticleContactGenerator {
public:
	NaiveParticleContactGenerator(float radius, std::vector<Particle*> particles);
	NaiveParticleContactGenerator() = default;

	void setVectorParticle(std::vector<Particle*> particles);

	//Radius of the particles
	float m_radius;

	std::vector<Particle*> m_particles;

	unsigned int addContact(std::vector<ParticleContact*>* contact, unsigned int  limit);

};