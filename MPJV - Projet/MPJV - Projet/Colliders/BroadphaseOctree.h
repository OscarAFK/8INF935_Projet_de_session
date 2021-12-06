#pragma once
#include <vector>
#include "ContactGeneratorBroadphase.h"

class BroadphaseOctree : ContactGeneratorBroadphase
{
public:
	BroadphaseOctree(std::vector<Rigidbody>* rigidbodies) : ContactGeneratorBroadphase(rigidbodies) {};
	~BroadphaseOctree() = default;

	unsigned int addContact(Contact* contact, unsigned int  limit);
}; 