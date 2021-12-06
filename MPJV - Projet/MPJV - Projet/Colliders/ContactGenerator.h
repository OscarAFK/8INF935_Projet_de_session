#pragma once
#include <vector>
#include "Contact.h"

class ContactGenerator
{
private:
	std::vector<Rigidbody>* m_rigidbodies;

public:
	ContactGenerator(std::vector<Rigidbody>* rigidbodies) :m_rigidbodies(rigidbodies) {};

	virtual unsigned int addContact(Contact* contact, unsigned int  limit) = 0;
};