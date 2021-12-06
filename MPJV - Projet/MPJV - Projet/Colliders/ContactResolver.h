#pragma once
#include <vector>
#include "Contact.h"

class ContactResolver
{
protected:
	unsigned int m_iteration;

public:

	ContactResolver() = default;

	void resolveContacts(Contact* contactArray,
						unsigned int numContact,
						float duration);
};