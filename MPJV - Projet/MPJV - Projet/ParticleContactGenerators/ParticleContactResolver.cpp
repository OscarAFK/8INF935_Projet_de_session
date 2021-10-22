#include "ParticleContactResolver.h"
#include <iostream>

void ParticleContactResolver::resolveContacts(std::vector<ParticleContact*> contactArray, unsigned int numContact, float duration)
{
	if (numContact == 0) return;
	m_iteration = 0;
	float smallestRelativeVelocity = 1000;
	do {
		ParticleContact *contactToResolve = nullptr;
		for (int i = 0; i < contactArray.size(); i++) {
			
			float currentVel = contactArray[i]->calculateSeperatingVelocity();
			if (currentVel < smallestRelativeVelocity) {
				smallestRelativeVelocity = currentVel;
				contactToResolve = contactArray[i];
			}
		}
		if (contactToResolve != nullptr)
			contactToResolve->resolve(duration);
		else
			break;
	} while (m_iteration < numContact * 2);

}
