#pragma once
#include "ForceGenerator.h"

class GravityForceGenerator : public ForceGenerator
{
private :
	Vector3D m_gravity;
public :
	//F = particle->GetMass()*m_gravity
	GravityForceGenerator(Vector3D gravity = Vector3D(0, -10, 0)) : m_gravity{ gravity } {};
	void UpdateForce(Rigidbody* rg, float duration) override;
};