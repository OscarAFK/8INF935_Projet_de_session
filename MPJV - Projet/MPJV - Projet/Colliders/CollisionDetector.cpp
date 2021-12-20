#include "CollisionDetector.h"

unsigned CollisionDetector::sphereAndSphere(const SphereCollider& one, const SphereCollider& two, CollisionData* data)
{
	if (data->contactLeft <= 0) return 0;
	Vector3D positionOne = one.getOffset()->getPosition(); //=============================================== calculer position en fonction de la transform+offset
	Vector3D positionTwo = two.getOffset()->getPosition(); //============================================== calculer position en fonction de la transform+offset

	Vector3D midline = positionOne - positionTwo;
	float size = midline.norm();

	if (size <= 0 || size >= one.getRadius() + two.getRadius()) return 0;	//Si les objets sont trop loin on ne retourne rien

	Vector3D normal = midline * (1/size);

	Contact* contact = new Contact();
	contact->m_contactNormal = normal;

	contact->m_contactPoint = positionOne + midline * 0.5f;
	contact->m_penetration = (one.getRadius() + two.getRadius() - size);
	// Write the appropriate data.
	contact->m_rigidbodies[0] = one.getRigidbody();
	contact->m_rigidbodies[1] = two.getRigidbody();
	//contact->m_restitution = data->m_restitution;
	data->contact.push_back(contact);
	//data->contact = contact;
	data->addContact(1);
	return 1;
}

unsigned CollisionDetector::sphereAndPlane(const SphereCollider& one, const PlaneCollider& two, CollisionData* data)
{
	if (data->contactLeft <= 0) return 0;

	Vector3D positionOne = one.getOffset()->getPosition();//============================================== calculer position en fonction de la transform+offset

	float ballDistance = Vector3D::scalarProduct(two.getNormal(), positionOne) - one.getRadius() - two.getPlaneOffset();

	if (ballDistance >= 0) return 0;

	// Create the contact - it has a normal in the plane direction.
	Contact* contact = new Contact();
	contact->m_contactNormal = two.getNormal();
	contact->m_penetration = -ballDistance;
	contact->m_contactPoint =
			positionOne - two.getNormal() * (ballDistance + one.getRadius());
	
	contact->m_rigidbodies[0] = one.getRigidbody();
	contact->m_rigidbodies[1] = two.getRigidbody();
	//contact->m_restitution = data->m_restitution;
	data->contact.push_back(contact);
	data->addContact(1);
	return 1;
}

unsigned CollisionDetector::sphereAndBox(const SphereCollider& sphere, const BoxCollider& box, CollisionData* data)
{
	if (data->contactLeft <= 0) return 0;
	Vector3D relCenterSphere = box.getRigidbody()->getOwner()->transform->getTransformMatrix().Inverse().TransformPosition(sphere.getOffset()->getPosition());//============================================== calculer position en fonction de la transform+offset

	//early check out
	if (abs(relCenterSphere.getX()) - sphere.getRadius() > box.getHalfSize().getX() ||
		abs(relCenterSphere.getY()) - sphere.getRadius() > box.getHalfSize().getY() ||
		abs(relCenterSphere.getZ()) - sphere.getRadius() > box.getHalfSize().getZ())
		return 0;

	Vector3D closestPoint = Vector3D(0, 0, 0);
	float dist;

	dist = relCenterSphere.getX();
	if (dist > box.getHalfSize().getX()) dist = box.getHalfSize().getX();
	if (dist < -box.getHalfSize().getX()) dist = -box.getHalfSize().getX();
	closestPoint.setX(dist);

	dist = relCenterSphere.getY();
	if (dist > box.getHalfSize().getY()) dist = box.getHalfSize().getY();
	if (dist < -box.getHalfSize().getY()) dist = -box.getHalfSize().getY();
	closestPoint.setY(dist);

	dist = relCenterSphere.getZ();
	if (dist > box.getHalfSize().getZ()) dist = box.getHalfSize().getZ();
	if (dist < -box.getHalfSize().getZ()) dist = -box.getHalfSize().getZ();
	closestPoint.setZ(dist);

	dist = (closestPoint - relCenterSphere).squareNorm();
	if (dist > sphere.getRadius() * sphere.getRadius()) return 0;

	Vector3D closestPtWorld = box.getRigidbody()->getOwner()->transform->getTransformMatrix().TransformPosition(closestPoint);//============================================== calculer position en fonction de la transform+offset

	Contact* contact = new Contact();
	contact->m_contactNormal = (sphere.getOffset()->getPosition() - closestPtWorld);
	contact->m_contactNormal = contact->m_contactNormal.normalize();
	contact->m_contactPoint = closestPtWorld;
	contact->m_penetration = sphere.getRadius() - sqrt(dist);

	contact->m_rigidbodies[0] = box.getRigidbody();
	contact->m_rigidbodies[1] = sphere.getRigidbody();
	//contact->m_restitution = data->m_restitution;
	data->contact.push_back(contact);
	data->addContact(1);
	return 1;
}

unsigned CollisionDetector::boxAndPlane(const BoxCollider& box, const PlaneCollider& plane, CollisionData* data)
{
	if (data->contactLeft <= 0) return 0;

	for(size_t i = 0; i < 8; i++)
	{
		// Calculate the distance from the plane with dot product(vertexPos, planeNormal)
		float vertexDistance = Vector3D::scalarProduct(box.getVertex(i), plane.getNormal()); //============================================== calculer position en fonction de la transform+offset

		// Compare this to the plane’s distance.
		if (vertexDistance <= plane.getPlaneOffset())
		{
			// Create the contact data.
			// The contact point is halfway between the vertex and the
			// plane - we multiply the direction by half the separation
			// distance and add the vertex location.
			Contact* contact = new Contact();
			contact->m_contactPoint = plane.getNormal();
			contact->m_contactPoint *= (vertexDistance-plane.getPlaneOffset());
			contact->m_contactPoint += box.getVertex(i);
			contact->m_contactNormal = plane.getNormal();
			contact->m_penetration = plane.getPlaneOffset() - vertexDistance;
			data->contact.push_back(contact);
			data->addContact(1);
		}
	}
}

unsigned CollisionDetector::boxAndBox(const BoxCollider& one, const BoxCollider& two, CollisionData* data)
{
	if (data->contactLeft <= 0) return 0;
	
	
	return 0;
}

float CollisionDetector::transformToAxis(const BoxCollider& box, const Vector3D& axis)
{
	return box.getHalfSize().getX() * abs(Vector3D::scalarProduct(axis,box.getOwner()->transform->getTransformMatrix().getAxisVector(0))) +
			box.getHalfSize().getY() * abs(Vector3D::scalarProduct(axis,box.getOwner()->transform->getTransformMatrix().getAxisVector(1))) +
			box.getHalfSize().getZ() * abs(Vector3D::scalarProduct(axis,box.getOwner()->transform->getTransformMatrix().getAxisVector(2)));
}

bool CollisionDetector::overlapOnAxis(const BoxCollider& one, const BoxCollider& two, const Vector3D& axis)
{
	float oneProject = transformToAxis(one, axis);
	float twoProject = transformToAxis(two, axis);

	Vector3D toCenter = one.getOwner()->transform->getTransformMatrix().getAxisVector(3) - one.getOwner()->transform->getTransformMatrix().getAxisVector(3);

	float distance = abs(Vector3D::scalarProduct(toCenter,axis));

	return (distance < oneProject + twoProject);
}

void CollisionData::addContact(int count)
{
	contactLeft -= count;
}
