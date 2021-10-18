#include "ParticleContact.h"

ParticleContact::ParticleContact(Particle* p1, Particle *p2, float restitution, float penetration) : 
                                m_particles{ p1,p2 }, m_restitution(restitution), m_penetration(penetration)
{
    if (p2 != nullptr) {
        m_contactNormal = (m_particles[0]->getPosition() - m_particles[1]->getPosition()).norm();
    }
    else {
        m_contactNormal = Vector3D(0,1,0);
    }
}

void ParticleContact::resolve(float duration)
{
    resolveVelocity();
    resolveInterpretation();
}

float ParticleContact::calculateSeperatingVelocity()
{
    if(m_particles[1]!=nullptr)
        return Vector3D::scalarProduct((m_particles[0]->getVelocity()- m_particles[1]->getVelocity()), m_contactNormal);
    else
        return Vector3D::scalarProduct(m_particles[0]->getVelocity(), m_contactNormal);
}

void ParticleContact::resolveVelocity()
{
}

void ParticleContact::resolveInterpretation()
{
}
