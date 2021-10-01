#include "Physics.h"

#pragma region Constructors
Physics::Physics() : m_particles{}
{
}

#pragma endregion

#pragma region Mutex

void Physics::addParticle(float invertedMass, float damping, Vector3D position, Vector3D velocity, Vector3D acceleration)
{
    m_particles.push_back(Particle(invertedMass, damping, position, velocity, acceleration));
}

void Physics::addParticle(Particle particle)
{
    m_particles.push_back(particle);
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

void Physics::update(float deltaTime)
{
    m_particleForceRegistry.updateForce(deltaTime);
    for (std::vector<Particle>::iterator it = m_particles.begin(); it != m_particles.end(); ++it) {
        it->integrate(deltaTime);
    }
}

void Physics::update()
{
    update((clock()- timeOfLastUpdate) / (double)CLOCKS_PER_SEC);
    timeOfLastUpdate = clock();
}

#pragma endregion