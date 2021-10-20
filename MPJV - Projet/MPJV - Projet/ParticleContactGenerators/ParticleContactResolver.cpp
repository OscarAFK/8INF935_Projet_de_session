#include "ParticleContactResolver.h"

void ParticleContactResolver::resolveContacts(ParticleContact* contactArray, unsigned int numContact, float duration)
{
	if (numContact == 0) return;
	m_iteration = 0;
	float smallestRelativeVelocity = 1000;
	do {
		ParticleContact *contactToResolve = nullptr;
		for (int i = 0; i < numContact; i++) {
			float currentVel = contactArray[i].calculateSeperatingVelocity();
			if (currentVel < smallestRelativeVelocity) {
				smallestRelativeVelocity = currentVel;
				contactToResolve = &contactArray[i];
			}
		}
		contactToResolve->resolve(duration);
	} while (m_iteration < numContact * 2 && smallestRelativeVelocity < 0);
}
