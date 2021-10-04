#pragma once

#include "Particle.h"
#include <vector>
#include <memory>
#include <chrono>
#include "ParticleForceGenerators/ParticleForceRegistry.h"

class Physics
{
	//The state of the world at a time
	struct State {
		std::vector<Particle> m_particles;

		ParticleForceRegistry m_particleForceRegistry;
	};

private:
	
	

	clock_t timeOfLastUpdate = clock();

	

public:

	State currentState;
	State previousState;

	Physics();
	~Physics() = default;

	void addParticle(float invertedMass = 0.0f, float damping = 0.0f, Vector3D position = Vector3D(), Vector3D velocity = Vector3D(), Vector3D acceleration = Vector3D());
	void addParticle(Particle particle);
	void removeParticle(int id);
	Particle* getParticle(int id);
	std::vector<Particle>* getAllParticle();
	std::vector<Particle>* getIntermediateParticle(const float alpha);
	void update(float t, float dt);
};