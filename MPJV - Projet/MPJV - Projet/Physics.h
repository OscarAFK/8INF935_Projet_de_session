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

class Physics
{
	//The state of the world at a time
	struct State {
		std::vector<Particle*> m_particles;

		ParticleForceRegistry m_particleForceRegistry;
	};

private:
	
	

	clock_t timeOfLastUpdate = clock();
	State currentState;
	State previousState;
	
	ParticleContactResolver particleContactResolver;
	NaiveParticleContactGenerator naiveParticleContactGenerator;
	std::vector<ParticleContactGenerator> particleContactGenerator;

public:

	Physics();
	~Physics() = default;

	void addParticle(float invertedMass = 0.0f, float damping = 0.0f, Vector3D position = Vector3D(), Vector3D velocity = Vector3D(), Vector3D acceleration = Vector3D());
	void addParticle(Particle*  particle);
	void addParticle(Particle* particle, std::vector<ParticleForceGenerator*> generators);
	void removeParticle(int id);
	Particle* getParticle(int id);
	std::vector<Particle*> getAllParticle();
	std::vector<Particle*> getIntermediateParticle(const float alpha);
	std::vector<ParticleContactGenerator>* getParticleContactGenerator();
	void updateState();
	void update(float t, float dt);
};