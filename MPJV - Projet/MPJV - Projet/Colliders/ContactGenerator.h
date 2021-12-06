#pragma once
#include <vector>
#include "Contact.h"

class ContactGenerator
{
public:
	virtual unsigned int addContact(Contact* contact, unsigned int  limit) = 0;
};