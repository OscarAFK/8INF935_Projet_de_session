#pragma once
#include "Entity.h"

class System
{
public:
	System() {};
	virtual void tick(std::vector<Entity*> entities) = 0;

private:

};