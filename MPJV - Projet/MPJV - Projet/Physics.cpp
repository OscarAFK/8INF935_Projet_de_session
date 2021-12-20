#include "Physics.h"
#include <iostream>
#include "Colliders/Octree.h"

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
    m_particles.push_back(Particle(invertedMass, damping, position, velocity, acceleration));
}

void Physics::addParticle(Particle particle)
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

#pragma region Mutex

/*void Physics::addRigidbody(Vector3D position, Quaternion orientation, float mass, float damping, float angularDamping, Matrix33 tenseurInertie)
{
    m_rigidbody.push_back(new Rigidbody(position, orientation, mass, damping, angularDamping, tenseurInertie));
}

void Physics::addRigidbody(Rigidbody * rigidbody)
{
    m_rigidbody.push_back(rigidbody);
}

void Physics::addRigidbody(Rigidbody *rigidbody, std::vector<ForceGenerator*> generators)
{
    m_rigidbody.push_back(rigidbody);
    for (int i = 0; i < generators.size(); i++)
    {
        m_forceRegistry.addEntry(m_rigidbody[m_rigidbody.size()-1], generators[i]);
    }
}

void Physics::removeRigidbody(int index)
{
    m_rigidbody.erase(m_rigidbody.begin() + index);
}*/


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

/*Rigidbody* Physics::getRigidbody(int id)
{
    return m_rigidbody[id];
}

std::vector<Rigidbody*> Physics::getAllRigidbody()
{
    return m_rigidbody;
}

std::vector<Rigidbody*> Physics::getIntermediateRigidbody(const float alpha)
{
    std::vector<Rigidbody*> intermediateRigidbody = std::vector<Rigidbody*>();
    for (int i = 0; i < m_rigidbody.size(); i++) {
        intermediateRigidbody.push_back(new Rigidbody(m_rigidbody[i]->GetPosition() * alpha + m_rigidbody[i]->GetPreviousPosition() * (1 - alpha)));
    }
    return intermediateRigidbody;
}*/

#pragma endregion

#pragma region Methods

void Physics::update(float t, float dt)
{
    m_particleForceRegistry.updateForce(dt);
    for (std::vector<Particle>::iterator it = m_particles.begin(); it != m_particles.end(); ++it) {
        it->integrate(dt);
    }

    m_forceRegistry.updateForce(dt);
    
    for (int i = 0; i < m_rigidbody.size(); i++) {
        m_rigidbody[i]->Integrate(dt);
    }

    //GESTION DES CONTACTS
    ParticleContact particleContactList[200];       //Création des contacts
    int nbContactsCrees = naiveParticleContactGenerator.addContact(particleContactList, CONTACT_MAX);
    for (int i = 0; i < particleContactGenerator.size(); i++) {
        nbContactsCrees+= particleContactGenerator[i]->addContact((particleContactList + nbContactsCrees), CONTACT_MAX-nbContactsCrees);
    }
    particleContactResolver.resolveContacts(particleContactList, nbContactsCrees, dt);          //Resolution des contacts
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


void Physics::tick(std::vector<Entity*> entities)
{
    float distanceFarthest = 0;

    for (size_t i = 0; i < entities.size(); i++)
    {
        float dist = entities[i]->transform->getPosition().getMax();
        if (dist > distanceFarthest) distanceFarthest = dist;
        Rigidbody* rigidbody = entities[i]->getComponent<Rigidbody>();
        ForceGenerator* forceGenerator = entities[i]->getComponent<ForceGenerator>();
        if (rigidbody != nullptr)
        {
            if (forceGenerator != nullptr) forceGenerator->UpdateForce(rigidbody,0.1f);
            rigidbody->Integrate(0.1f);
        }
    }

    //COLLISIONS
    std::vector<OctreeObject*> octreeObjects;
    for (size_t i = 0; i < entities.size(); i++)
    {
        if (!entities[i]->getComponent<Collider>()) continue;
        OctreeObject* octreeObject = new OctreeObject(entities[i]);
        octreeObjects.push_back(octreeObject);
    }
    if (octreeObjects.size() == 0) return;
    OctreeNode* entryNode = new OctreeNode();
    entryNode->BuildOctree(Vector3D::zero(), distanceFarthest, 5); //on prend une profondeur totalement arbitraire
    for (int i = 0; i < octreeObjects.size(); i++) {
        entryNode->InsertObject(octreeObjects[i]);
    }

    CollisionData data;
    data.contactLeft = 50;
    entryNode->TestAllCollisions(&data);
    if (data.contactLeft != 50) {
        std::cout << "cool";
    }
    if (data.contactLeft < 50) { 
        std::cout << "Contact normal: " << data.contact->m_contactNormal.to_string() << std::endl;
    }
}
#pragma endregion