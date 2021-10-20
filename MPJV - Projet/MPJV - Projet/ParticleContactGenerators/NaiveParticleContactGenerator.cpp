#include "NaiveParticleContactGenerator.h"

unsigned int NaiveParticleContactGenerator::addContact(ParticleContact* contact, unsigned int limit)
{
	int iteration=0;
	for (int i = 0; i < m_particles.size(); i++) {
		for (int j = 0; j < m_particles.size(); j++) {
			if (iteration > limit) {
				return 1;
			}
			if (i == j) continue;
			float distance = (m_particles[i].getPosition() - m_particles[j].getPosition()).Vector3D::norm();
			if (distance < m_radius) {
				contact = new ParticleContact(&m_particles[0], &m_particles[1], 0, m_radius-distance);
				contact++;
				iteration++;
			}
		}
	}
	return 0;
}
