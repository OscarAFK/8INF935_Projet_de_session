#pragma once
#include "ForceGenerator.h"

class SpringForceGenerator : public ForceGenerator
{
private :
	Vector3D m_bodyAnchor = Vector3D(0,0,0);

	Rigidbody* m_otherRgbd = nullptr;

	Vector3D m_otherBodyAnchor = Vector3D(0, 0, 0);

	//spring parameter
	float m_k;
	float m_restLength;

public :
	//F = particle->GetMass()*m_gravity
	SpringForceGenerator(Entity* owner) : ForceGenerator(owner) { m_name = "Force Spring"; };
	void Initialize(Vector3D bodyAnchor, Rigidbody * rgbd, Vector3D otherBodyAnchor, float k, float restLength);
	void UpdateForce(Rigidbody* rg, float duration) override;
	void renderComponentUI();
};