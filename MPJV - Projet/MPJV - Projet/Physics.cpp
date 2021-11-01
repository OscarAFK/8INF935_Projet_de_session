#include "Physics.h"
#include <iostream>

#pragma region Constructors
Physics::Physics()
{
    particleContactResolver = ParticleContactResolver();
    naiveParticleContactGenerator = NaiveParticleContactGenerator(100,getAllParticle());
}

#pragma endregion

#pragma region Mutex

void Physics::addParticle(float invertedMass, float damping, Vector3D position, Vector3D velocity, Vector3D acceleration)
{
    m_particles.push_back(new Particle(invertedMass, damping, position, velocity, acceleration));
}

void Physics::addParticle(Particle *particle)
{
    m_particles.push_back(particle);
}

void Physics::addParticle(Particle * particle, std::vector<ParticleForceGenerator*> generators)
{
    m_particles.push_back(*particle);
    for (int i = 0; i < generators.size(); i++)
    {
        m_particleForceRegistry.addEntry(particle, generators[i]);
    }
}

void Physics::removeParticle(int index)
{
    m_particles.erase(m_particles.begin() + index);
}

#pragma endregion

#pragma region Accessors

Particle* Physics::getParticle(int id)
{
    return &m_particles[id];
}

std::vector<Particle>* Physics::getAllParticle()
{
    return &m_particles;
}

#pragma endregion

#pragma region Methods

void Physics::update(float t, float dt)
{
    m_particleForceRegistry.updateForce(dt);
    for (std::vector<Particle>::iterator it = m_particles.begin(); it != m_particles.end(); ++it) {
        it->integrate(dt);
    }

    //GESTION DES CONTACTS
    std::vector<ParticleContact> particleContactList;       //Création des contacts
    int nbContactsCrees = naiveParticleContactGenerator.addContact(&particleContactList,100);
    for (int i = 0; i < particleContactGenerator.size(); i++) {
        nbContactsCrees+= particleContactGenerator[i]->addContact(&particleContactList, 100);
    }
    particleContactResolver.resolveContacts(&particleContactList, nbContactsCrees, dt);          //Resolution des contacts
}

std::vector<Particle*> Physics::getIntermediateParticle(const float alpha)
{
    std::vector<Particle*> intermediateParticles = std::vector<Particle*>();
    for (int i = 0; i < m_particles.size(); i++) {
        intermediateParticles.push_back(new Particle(m_particles[i].getPosition() * alpha + m_particles[i].getPreviousPosition() * (1-alpha)));
    }
    return intermediateParticles;
}

void Physics::addParticleContactGenerator(ParticleContactGenerator* contactGenerator)
{
    particleContactGenerator.push_back(contactGenerator);
}

#pragma endregion