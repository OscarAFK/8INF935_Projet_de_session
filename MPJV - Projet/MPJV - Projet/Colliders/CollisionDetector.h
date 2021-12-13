#pragma once
#include "Contact.h"
#include "Collider.h"
#include "SphereCollider.h"
#include "PlaneCollider.h"
#include "BoxCollider.h"

struct CollisionData{
	Contact* contact;

	int contactLeft;
};

class CollisionDetector {
public:
	/*static void detectContacts(const Collider& firstCollider,
		const Collider& secondCollider,
		CollisionData* data);*/

	static unsigned sphereAndSphere(const SphereCollider& one,
		const SphereCollider& two,
		CollisionData* data);

	static unsigned sphereAndPlane(const SphereCollider& one,
		const PlaneCollider& two,
		CollisionData* data);

	static unsigned boxAndPlane(const BoxCollider& one,
		const PlaneCollider& two,
		CollisionData* data);

	static unsigned boxAndBox(const BoxCollider& one,
		const BoxCollider& two,
		CollisionData* data);
};