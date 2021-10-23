#pragma once
#include "../Particle.h"
#include "../Vector3D.h"

class ParticleContact
{
public:	

	ParticleContact(Particle *p1, Particle *p2, float restitution, float penetration);
	ParticleContact() = default;
	~ParticleContact() = default;

	void resolve(float duration);
	
	float calculateSeperatingVelocity();

	Particle* m_particles[2];

	//elasticness
	float m_restitution;

	//penetration of the contact
	float m_penetration;

	Vector3D m_contactNormal;

private:
	void resolveVelocity();

	void resolveInterpretation();
};