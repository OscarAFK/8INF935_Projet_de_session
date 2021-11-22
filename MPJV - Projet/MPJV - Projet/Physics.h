#pragma once

#include "Particle.h"
#include <vector>
#include <memory>
#include <chrono>
#include "ParticleForceGenerators/ParticleForceRegistry.h"
#include "ParticleForceGenerators/ParticleAnchoredElastic.h"
#include "ParticleForceGenerators/ParticleAnchoredSpring.h"
#include "ParticleForceGenerators/ParticleBuoyancy.h"
#include "ParticleForceGenerators/ParticleDrag.h"
#include "ParticleForceGenerators/ParticleElastic.h"
#include "ParticleForceGenerators/ParticleGravity.h"
#include "ParticleForceGenerators/ParticleSpring.h"
#include "ParticleContactGenerators/ParticleContactResolver.h"
#include "ParticleContactGenerators/ParticleContactGenerator.h"
#include "ParticleContactGenerators/NaiveParticleContactGenerator.h"
#include "ParticleContactGenerators/ParticleCable.h"
#include "Utilitaire/Rigidbody.h"

#define CONTACT_MAX		200

class Physics
{

private:
	
	std::vector<Particle> m_particles;
	std::vector<Rigidbody> m_rigidbody;

	ParticleForceRegistry m_particleForceRegistry;

	clock_t timeOfLastUpdate = clock();
	
	ParticleContactResolver particleContactResolver;
	NaiveParticleContactGenerator naiveParticleContactGenerator;
	std::vector<ParticleContactGenerator*> particleContactGenerator;


public:

	Physics();
	~Physics() = default;

	void addParticle(float invertedMass = 0.0f, float damping = 0.0f, Vector3D position = Vector3D(), Vector3D velocity = Vector3D(), Vector3D acceleration = Vector3D());
	void addParticle(Particle particle);
	void addParticle(Particle* particle, std::vector<ParticleForceGenerator*> generators);
	void removeParticle(int id);
	Particle* getParticle(int id);
	std::vector<Particle>* getAllParticle();
	std::vector<Particle*> getIntermediateParticle(const float alpha);
	void addParticleContactGenerator(ParticleContactGenerator* contactGenerator);
	void update(float t, float dt);

	void addRigidbody(Vector3D position = Vector3D(), Quaternion orientation = Quaternion(), float mass = 0.0f, float damping= 0.0f, float angularDamping = 0.0f, Matrix33 tenseurInertie = Matrix33());
	void addRigidbody(Rigidbody rigidbody);
	void removeRigidbody(int id);
	Rigidbody* getRigidbody(int id);
	std::vector<Rigidbody>* getAllRigidbody();
	
};