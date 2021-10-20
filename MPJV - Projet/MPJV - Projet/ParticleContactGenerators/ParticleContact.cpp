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
    float k;
    if (m_particles[1] != nullptr) {    //Si on a définit une seconde particule, on l'utilise pour calculer k et on change sa velocité
         k = ((m_restitution + 1) * Vector3D::scalarProduct(m_particles[0]->getVelocity() - m_particles[1]->getVelocity(), m_contactNormal))
            / (m_particles[0]->getInverseMass() + m_particles[1]->getInverseMass());
         m_particles[1]->setVelocity(m_particles[1]->getVelocity() - k * m_contactNormal * m_particles[1]->getInverseMass());
    }
    else {      //Sinon on calcule k en considérant l'objet de contact comme ayant une vitesse nulle et une masse inversée nulle (=masse infinie)
        k = ((m_restitution + 1) * Vector3D::scalarProduct(m_particles[0]->getVelocity(), m_contactNormal))
            / (m_particles[0]->getInverseMass());
    }
    
    //Et dans tout les cas on change la vélocité de la première particule
    m_particles[0]->setVelocity(m_particles[0]->getVelocity() - k * m_contactNormal * m_particles[0]->getInverseMass());
}

void ParticleContact::resolveInterpretation()
{
}
