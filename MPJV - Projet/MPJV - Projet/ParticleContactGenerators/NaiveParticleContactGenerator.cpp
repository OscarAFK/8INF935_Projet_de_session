#include "NaiveParticleContactGenerator.h"
#include <iostream>

NaiveParticleContactGenerator::NaiveParticleContactGenerator(float radius, std::vector<Particle*> particles) : m_radius(radius)
{
	m_particles = particles;
}

void NaiveParticleContactGenerator::setVectorParticle(std::vector<Particle*> particles)
{
	m_particles = particles;
}

unsigned int NaiveParticleContactGenerator::addContact(std::vector<ParticleContact*>* contact, unsigned int  limit) 
{
	int iteration=0;
	for (int i = 0; i < m_particles.size(); i++) {
		for (int j = 0; j < m_particles.size(); j++) {
			if (i == j) continue;
			float distance = (m_particles[i]->getPosition() - m_particles[j]->getPosition()).Vector3D::norm();
			if (distance < m_radius) {

				ParticleContact* c = new ParticleContact(m_particles[i], m_particles[j], 1, m_radius - distance);
				
				//On vérifie si le contact n'existe pas déjà
				bool contactAlreadyExist = false;
				for (int i = 0; i < contact->size(); i++) {
					if (*contact->at(i) == *c) {
						contactAlreadyExist = true; break;
					}
				}
				
				if(!contactAlreadyExist){
					contact->push_back(c);
					iteration++;
				}
			}
		}
	}
	return iteration;
}
