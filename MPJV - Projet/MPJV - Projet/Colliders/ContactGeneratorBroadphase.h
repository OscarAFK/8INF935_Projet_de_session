#pragma once
#include <vector>
#include "Contact.h"

class ContactGeneratorBroadphase
{
private:
	std::vector<Rigidbody>* m_rigidbodies;

public:
	ContactGeneratorBroadphase(std::vector<Rigidbody>* rigidbodies) :m_rigidbodies(rigidbodies) {};

	virtual unsigned int addContact(Contact* contact, unsigned int  limit) = 0;
};