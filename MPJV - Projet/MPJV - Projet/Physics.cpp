#include "Physics.h"

#pragma region Constructors
Physics::Physics() : m_particles{}, m_incrementalId{0}
{
}

#pragma endregion

#pragma region Mutex

void Physics::addParticle(float invertedMass, float damping, Vector3D position, Vector3D velocity, Vector3D acceleration)
{
    m_particles[m_incrementalId] = Particle(invertedMass, damping, position, velocity,acceleration);
    m_incrementalId++;
}

void Physics::removeParticle(int id)
{
    m_particles.erase(id);
}

#pragma endregion

#pragma region Accessors

std::shared_ptr<Particle> Physics::getParticle(int id)
{
    return std::make_shared<Particle>(m_particles[id]);
}

#pragma endregion

#pragma region Methods

void Physics::update(float deltaTime)
{
    for (std::map<int, Particle>::iterator it = m_particles.begin(); it != m_particles.end(); ++it) {
        it->second.integrate(deltaTime);
    }
}

#pragma endregion