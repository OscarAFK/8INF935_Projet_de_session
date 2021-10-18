#include "ParticleContact.h"

ParticleContact::ParticleContact(Particle* p1, Particle *p2, float restitution, float penetration, Vector3D contactNormal) : 
                                m_particles{ p1,p2 }, m_restitution(restitution), m_penetration(penetration), m_contactNormal(contactNormal)
{
}

void ParticleContact::resolve(float duration)
{
}

float ParticleContact::calculateSeperatingVelocity()
{
    return 0.0f;
}

void ParticleContact::resolveVelocity()
{
}

void ParticleContact::handleInterpretation()
{
}
