#include "CollisionDetector.h"

unsigned CollisionDetector::sphereAndSphere(const SphereCollider& one, const SphereCollider& two, CollisionData* data)
{
	if (data->contactLeft <= 0) return 0;

	Vector3D positionOne = one.getOffset();
	Vector3D positionTwo = two.getOffset();

	Vector3D midline = positionOne - positionTwo;
	float size = midline.norm();

	if (size <= 0 || size >= one.getRadius() + two.getRadius()) return 0;	//Si les objets sont trop loin on ne retourne rien

	Vector3D normal = midline * (1/size);

	Contact* contact = data->contact;
	contact->m_contactNormal = normal;

	contact->m_contactPoint = positionOne + midline * 0.5f;
	contact->m_penetration = (one.getRadius() + two.getRadius() - size);
	// Write the appropriate data.
	contact->m_rigidbodies[0] = one.getRigidbody();
	contact->m_rigidbodies[1] = two.getRigidbody();
	//contact->m_restitution = data->m_restitution;
	//contact->friction = data->friction;
	return 1;
}

unsigned CollisionDetector::sphereAndPlane(const SphereCollider& one, const PlaneCollider& two, CollisionData* data)
{
	if (data->contactLeft <= 0) return 0;

	Vector3D positionOne = one.getOffset();

	float ballDistance = Vector3D::scalarProduct(two.getNormal(), positionOne) - one.getRadius() - two.getPlaneOffset();

	if (ballDistance >= 0) return 0;

	// Create the contact - it has a normal in the plane direction.
	Contact* contact = data->contact;
	contact->m_contactNormal = two.getNormal();
	contact->m_penetration = -ballDistance;
	contact->m_contactPoint =
			positionOne - two.getNormal() * (ballDistance + one.getRadius());
	
	contact->m_rigidbodies[0] = one.getRigidbody();
	contact->m_rigidbodies[1] = two.getRigidbody();
	//contact->m_restitution = data->m_restitution;
	//contact->friction = data->friction;
	return 1;
}

unsigned CollisionDetector::boxAndPlane(const BoxCollider& one, const PlaneCollider& two, CollisionData* data)
{
	if (data->contactLeft <= 0) return 0;


}

unsigned CollisionDetector::boxAndBox(const BoxCollider& one, const BoxCollider& two, CollisionData* data)
{
}
