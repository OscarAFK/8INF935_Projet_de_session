#include "Physics.h"
#include <iostream>

#pragma region Constructors
Physics::Physics()
{
    particleContactResolver = ParticleContactResolver();
    particleContactGenerator = NaiveParticleContactGenerator(50,getAllParticle());
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
    for (int i = 0; i < previousState.m_particles.size(); i++)
        previousState.m_particles[i] = new Particle(currentState.m_particles[i]);
    previousState = currentState;
    particleContactGenerator.setVectorParticle(getAllParticle());
}

void Physics::update(float t, float dt)
{
    updateState();
    currentState.m_particleForceRegistry.updateForce(dt);
    for (std::vector<Particle*>::iterator it = currentState.m_particles.begin(); it != currentState.m_particles.end(); ++it) {
        (*it)->integrate(dt);
    }
    std::vector<ParticleContact*> particleContactList;
    int nbContactsCrees = particleContactGenerator.addContact(&particleContactList,100);
    std::cout << "size de particleContactList: " << particleContactList.size() << std::endl;
    std::cout << "size de nbContactsCrees: " << nbContactsCrees << std::endl;
    particleContactResolver.resolveContacts(particleContactList, nbContactsCrees, dt);

}

std::vector<Particle*> Physics::getIntermediateParticle(const float alpha)
{
    std::vector<Particle*> intermediateParticles = std::vector<Particle*>();
    for (int i = 0; i < previousState.m_particles.size(); i++) {
        intermediateParticles.push_back(new Particle(currentState.m_particles[i]->getPosition() * alpha + previousState.m_particles[i]->getPosition() * (1-alpha)));
    }
    return intermediateParticles;
}

#pragma endregion