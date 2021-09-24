#pragma once

#include "Particle.h"
#include <map>
#include <memory>

class Physics
{
private:

	int m_incrementalId;
	std::map<int, Particle> m_particles;

public:
	Physics();
	~Physics() = default;

	void addParticle(float invertedMass = 0.0f, float damping = 0.0f, Vector3D position = Vector3D(), Vector3D velocity = Vector3D(), Vector3D acceleration = Vector3D());
	void removeParticle(int id);
	std::shared_ptr<Particle> getParticle(int id);
	std::shared_ptr<std::map<int, Particle>> getAllParticle();
	void update(float deltaTime);
};

