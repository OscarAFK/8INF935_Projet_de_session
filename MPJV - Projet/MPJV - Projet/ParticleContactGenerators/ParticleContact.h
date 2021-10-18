#include "../Particle.h"
#include "../Vector3D.h"

class ParticleContact
{
public:	

	ParticleContact(Particle *p1, Particle *p2, float restitution, float penetration, Vector3D contactNormal);
	~ParticleContact() = default;

	void resolve(float duration);
	
	float calculateSeperatingVelocity();

private:
	Particle* m_particles[2];

	float m_restitution;

	float m_penetration;

	Vector3D m_contactNormal;

	void resolveVelocity();

	void handleInterpretation();
};