#include "ContactResolver.h"

void ContactResolver::resolveContacts(Contact* contactArray, unsigned int numContact, float duration)
{
	//Cette fonction est à retravailler
	if (numContact == 0) return;
	m_iteration = 0;
	float smallestRelativeVelocity = 1000;
	while (m_iteration < numContact) {
		Contact* contactToResolve = nullptr;
		for (int i = 0; i < numContact; i++) {
			float currentVel = (contactArray + i)->calculateSeperatingVelocity();
			if (currentVel < smallestRelativeVelocity) {
				smallestRelativeVelocity = currentVel;
				contactToResolve = (contactArray + i);
			}
		}
		if (contactToResolve == nullptr) {
			contactToResolve = (contactArray);
		}
		contactToResolve->resolve(duration);

		m_iteration++;

	}
}
