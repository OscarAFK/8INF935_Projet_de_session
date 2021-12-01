#pragma once
#include "../Utilitaire/Rigidbody.h"

class ForceGenerator
{
public :
	virtual void UpdateForce(Rigidbody* rg, float deltaTime) = 0;
};