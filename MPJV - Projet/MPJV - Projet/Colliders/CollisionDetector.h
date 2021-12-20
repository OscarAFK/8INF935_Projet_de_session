#pragma once
#include "Contact.h"
#include "Collider.h"
#include "SphereCollider.h"
#include "PlaneCollider.h"
#include "BoxCollider.h"

struct CollisionData{
	std::vector<Contact*> contact;

	int contactLeft;

	void addContact(int count);
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

	static unsigned sphereAndBox(const SphereCollider& one,
		const BoxCollider& two,
		CollisionData* data);

	static unsigned boxAndPlane(const BoxCollider& one,
		const PlaneCollider& two,
		CollisionData* data);

	static unsigned boxAndBox(const BoxCollider& one,
		const BoxCollider& two,
		CollisionData* data);

	static float transformToAxis(const BoxCollider& box, const Vector3D &axis);
	static bool overlapOnAxis(const BoxCollider& one, const BoxCollider& two, const Vector3D &axis);
};