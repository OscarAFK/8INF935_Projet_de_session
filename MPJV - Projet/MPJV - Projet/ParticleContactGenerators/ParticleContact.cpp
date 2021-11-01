#include "ParticleContact.h"
#include <iostream>

ParticleContact::ParticleContact(Particle* p1, Particle *p2, float restitution, float penetration) : 
                                m_restitution(restitution), m_penetration(penetration)
{
    m_particles[0] = p1;
    m_particles[1] = p2;
    if (p2 != nullptr) {
        m_contactNormal = (m_particles[0]->getPosition() - m_particles[1]->getPosition()).normalize();
;    }
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

bool ParticleContact::operator==(const ParticleContact c)
{
    if ((c.m_particles[0] == m_particles[0] && c.m_particles[1] == m_particles[1]) ||       //Si le contact pointe vers deux particules identiques
        (c.m_particles[0] == m_particles[1] && c.m_particles[1] == m_particles[0]))         //dans n'importe quel ordre, alors il est identique
        return true;
    else return false;
}

void ParticleContact::resolveVelocity()
{
    float k;
    float numerateur;
    float denominateur;
    if (m_particles[1] != nullptr) {    //Si on a définit une seconde particule, on l'utilise pour calculer k
        
        numerateur = (m_restitution + 1) * Vector3D::scalarProduct(m_particles[0]->getVelocity() - m_particles[1]->getVelocity(), m_contactNormal);
        denominateur = (m_particles[0]->getInverseMass() + m_particles[1]->getInverseMass());
    }
    else {      //Sinon on calcule k en considérant l'objet de contact comme ayant une vitesse nulle et une masse inversée nulle (=masse infinie)
        
        numerateur = ((m_restitution + 1) * Vector3D::scalarProduct(m_particles[0]->getVelocity(), m_contactNormal));
        denominateur = (m_particles[0]->getInverseMass());
    }

    k = numerateur / denominateur;

    m_particles[0]->setVelocity(m_particles[0]->getVelocity() - k * m_contactNormal * m_particles[0]->getInverseMass());
    if (m_particles[1]) m_particles[1]->setVelocity(m_particles[1]->getVelocity() + k * m_contactNormal * m_particles[1]->getInverseMass());
}

void ParticleContact::resolveInterpretation()
{
    if (m_particles[1] != nullptr) {    //Si on définit une seconde particule, alors on calcule la distance dont chaque particule doit être déplacée
        m_particles[0]->setPosition(m_particles[0]->getPosition() + (m_particles[1]->getMass() / (m_particles[0]->getMass() + m_particles[1]->getMass()) * m_penetration * m_contactNormal));
        m_particles[1]->setPosition(m_particles[1]->getPosition()+(-m_particles[0]->getMass()/ (m_particles[0]->getMass() + m_particles[1]->getMass()) * m_penetration * m_contactNormal));
    }
    else {  //Sinon on déplace juste la première particule de toute la distance d'interpénétration
        m_particles[0]->setPosition(m_particles[0]->getPosition() + m_penetration * m_contactNormal);
    }
    
}
