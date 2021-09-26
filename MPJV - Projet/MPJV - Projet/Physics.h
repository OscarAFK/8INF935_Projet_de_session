#pragma once

#include "Particle.h"
#include <map>
#include <memory>
#include <chrono>

class Physics
{
private:

	//A variable that keep track of the id of the last particle created
	int m_incrementalId;

	//A map containing all particles, with an associated id
	std::map<int, Particle> m_particles;

	clock_t timeOfLastUpdate = clock();

	void update(float deltaTime);

public:
	Physics();
	~Physics() = default;

	void addParticle(float invertedMass = 0.0f, float damping = 0.0f, Vector3D position = Vector3D(), Vector3D velocity = Vector3D(), Vector3D acceleration = Vector3D());
	void addParticle(Particle particle);
	void removeParticle(int id);
	std::shared_ptr<Particle> getParticle(int id);
	std::shared_ptr<std::map<int, Particle>> getAllParticle();
	void update();
};

