#pragma once
#include <vector>
#include "ContactGenerator.h"

class ContactGeneratorQuadtree : ContactGenerator
{
public:
	ContactGeneratorQuadtree(std::vector<Rigidbody>* rigidbodies) : ContactGenerator(rigidbodies) {};
	~ContactGeneratorQuadtree() = default;

	unsigned int addContact(Contact* contact, unsigned int  limit);
}; 