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
    currentState.m_particles.push_back(new Particle(invertedMass, damping, position, velocity, acceleration));
}

void Physics::addParticle(Particle *particle)
{
    currentState.m_particles.push_back(particle);
}

void Physics::addParticle(Particle * particle, std::vector<ParticleForceGenerator*> generators)
{
    currentState.m_particles.push_back(particle);
    for (int i = 0; i < generators.size(); i++)
    {
        currentState.m_particleForceRegistry.addEntry(currentState.m_particles[currentState.m_particles.size() - 1], generators[i]);
    }
}

void Physics::removeParticle(int index)
{
    currentState.m_particles.erase(currentState.m_particles.begin() + index);
}

#pragma endregion

#pragma region Accessors

Particle* Physics::getParticle(int id)
{
    return currentState.m_particles[id];
}

std::vector<Particle*> Physics::getAllParticle()
{
    std::vector<Particle*> allParticles;
    for (int i = 0; i < currentState.m_particles.size(); i++) {
        allParticles.push_back(currentState.m_particles[i]);
    }
    return allParticles;
}

#pragma endregion

#pragma region Methods

void Physics::updateState()
{
    previousState.m_particles.clear();

    for (int i = 0; i < previousState.m_particles.size(); i++)
        previousState.m_particles.push_back(new Particle(currentState.m_particles[i]));
    previousState = currentState;
    naiveParticleContactGenerator.setVectorParticle(getAllParticle());
}

void Physics::update(float t, float dt)
{
    updateState();
    currentState.m_particleForceRegistry.updateForce(dt);
    for (std::vector<Particle*>::iterator it = currentState.m_particles.begin(); it != currentState.m_particles.end(); ++it) {
        (*it)->integrate(dt);
    }

    //GESTION DES CONTACTS
    std::vector<ParticleContact*> particleContactList;                                          //Création des contacts
    int nbContactsCrees = naiveParticleContactGenerator.addContact(&particleContactList,100);
    for (int i = 0; i < particleContactGenerator.size(); i++) {
        nbContactsCrees+= particleContactGenerator[i]->addContact(&particleContactList, 100);
    }
    particleContactResolver.resolveContacts(particleContactList, nbContactsCrees, dt);          //Resolution des contacts
    for (int i = 0; i < particleContactList.size(); i++) {                                      //Nettoyage
        delete particleContactList[i];
    }
}

std::vector<Particle*> Physics::getIntermediateParticle(const float alpha)
{
    std::vector<Particle*> intermediateParticles = std::vector<Particle*>();
    for (int i = 0; i < previousState.m_particles.size(); i++) {
        intermediateParticles.push_back(new Particle(currentState.m_particles[i]->getPosition() * alpha + previousState.m_particles[i]->getPosition() * (1-alpha)));
    }
    return intermediateParticles;
}

void Physics::addParticleContactGenerator(ParticleContactGenerator* contactGenerator)
{
    particleContactGenerator.push_back(contactGenerator);
}

#pragma endregion