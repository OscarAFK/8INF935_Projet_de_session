#pragma once
#include "../Utilitaire/Rigidbody.h"
#include "../Component.h"

class ForceGenerator : public Component
{
public :
	ForceGenerator(Entity* owner) : Component(owner) {};
	virtual void UpdateForce(Rigidbody* rg, float deltaTime) = 0;
};