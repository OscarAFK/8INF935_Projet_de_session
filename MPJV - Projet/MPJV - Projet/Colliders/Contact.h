#pragma once
#include "../Utilitaire/Rigidbody.h"
#include "../Vector3D.h"

class Contact
{
public:	

	Contact(Rigidbody *r1, Rigidbody *r2, float restitution, float penetration);
	Contact() = default;
	~Contact() = default;

	void resolve(float duration);
	
	float calculateSeperatingVelocity();

	Rigidbody* m_rigidbodies[2];

	//elasticness
	float m_restitution;

	//penetration of the contact
	float m_penetration;

	Vector3D m_contactNormal;
	Vector3D m_contactPoint;

private:
	//void resolveVelocity();
	//void resolveInterpretation();
};