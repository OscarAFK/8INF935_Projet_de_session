#pragma once
#include "ForceGenerator.h"

class GravityForceGenerator : public ForceGenerator
{
private :
	Vector3D m_gravity;
public :
	//F = particle->GetMass()*m_gravity
	GravityForceGenerator(Entity* owner) : ForceGenerator(owner) { m_name = "Force Gravity"; };
	void Initialize(Vector3D gravity = Vector3D(0, -10, 0));
	void UpdateForce(Rigidbody* rg, float duration) override;
	void renderComponentUI();
};