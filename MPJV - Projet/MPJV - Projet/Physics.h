#pragma once

#include "Particle.h"
#include <vector>
#include <memory>
#include <chrono>

class Physics
{
private:

	//A variable that keep track of the id of the last particle created
	int m_incrementalId;

	//A map containing all particles, with an associated id
	std::vector<Particle> m_particles;

	clock_t timeOfLastUpdate = clock();

	void update(float deltaTime);

public:
	Physics();
	~Physics() = default;

	void addParticle(float invertedMass = 0.0f, float damping = 0.0f, Vector3D position = Vector3D(), Vector3D velocity = Vector3D(), Vector3D acceleration = Vector3D());
	void addParticle(Particle particle);
	void removeParticle(int id);
	std::shared_ptr<Particle> getParticle(int id);
	std::shared_ptr<std::vector<Particle>> getAllParticle();
	void update();
};

