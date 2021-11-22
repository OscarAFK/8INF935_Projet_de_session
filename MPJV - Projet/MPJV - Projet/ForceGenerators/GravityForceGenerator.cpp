#include "GravityForceGenerator.h"
#include <iostream>

void GravityForceGenerator::UpdateForce(Rigidbody* rg, float deltaTime)
{
	rg->AddForce(rg->GetMass() * m_gravity);
}
