#include "NaiveParticleContactGenerator.h"

NaiveParticleContactGenerator::NaiveParticleContactGenerator(float radius, std::vector<Particle>* particles) : m_radius(radius)
{
	m_particles = particles;
}

void NaiveParticleContactGenerator::setVectorParticle(std::vector<Particle>* particles)
{
	m_particles = particles;
}

unsigned int NaiveParticleContactGenerator::addContact(ParticleContact* contact, unsigned int limit)
{
	int iteration=0;
	for (int i = 0; i < m_particles->size(); i++) {
		for (int j = 0; j < m_particles->size(); j++) {
			if (iteration > limit) {
				return limit;
			}
			if (i == j) continue;
			float distance = (m_particles->at(i).getPosition() - m_particles->at(j).getPosition()).Vector3D::norm();
			if (distance < m_radius) {
				contact = new ParticleContact(&(m_particles->at(i)), &(m_particles->at(j)), 0, m_radius-distance);
				contact++;
				iteration++;
			}
		}
	}
	return iteration;
}
