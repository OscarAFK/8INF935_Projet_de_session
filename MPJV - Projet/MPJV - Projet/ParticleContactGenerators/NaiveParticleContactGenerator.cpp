#include "NaiveParticleContactGenerator.h"
#include <iostream>

NaiveParticleContactGenerator::NaiveParticleContactGenerator(float radius, std::vector<Particle>* particles) : m_radius(radius)
{
	m_particles = particles;
}

unsigned int NaiveParticleContactGenerator::addContact(ParticleContact* contact, unsigned int  limit) 
{
	int iteration=0;
	for (int i = 0; i < m_particles->size(); i++) {
		for (int j = i; j < m_particles->size(); j++) {
			if (i == j) continue;
			float distance = (m_particles->at(i).getPosition() - m_particles->at(j).getPosition()).Vector3D::norm();

			if (distance < m_radius) {
				ParticleContact c = ParticleContact(&m_particles->at(i), &m_particles->at(j), 1, m_radius - distance);
				*(contact+iteration) = c;
				iteration++;
				if (iteration >= limit-1) return iteration;
			}
		}
	}
	return iteration;
}
