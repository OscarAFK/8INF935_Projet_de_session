#include "ParticleContactResolver.h"
#include <iostream>

void ParticleContactResolver::resolveContacts(ParticleContact* contactArray, unsigned int numContact, float duration)
{
	if (numContact == 0) return;
	m_iteration = 0;
	float smallestRelativeVelocity = 1000;
	do {
		ParticleContact *contactToResolve = nullptr;
		for (int i = 0; i < numContact; i++) {
			std::cout << "Iteration no : " << i << std::endl;
			float currentVel = contactArray[i].calculateSeperatingVelocity();
			std::cout << "Separating Velocity calculée" << std::endl;
			if (currentVel < smallestRelativeVelocity) {
				smallestRelativeVelocity = currentVel;
				contactToResolve = &contactArray[i];
			}
		}
		contactToResolve->resolve(duration);
	} while (m_iteration < numContact * 2 && smallestRelativeVelocity < 0);
}
