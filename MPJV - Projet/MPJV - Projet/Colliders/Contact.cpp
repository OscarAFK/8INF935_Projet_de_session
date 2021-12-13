#include "Contact.h"

Contact::Contact(Rigidbody* r1, Rigidbody* r2, float restitution, float penetration) :
												m_restitution(restitution), m_penetration(penetration)
{
	m_rigidbodies[0] = r1;
	m_rigidbodies[1] = r2;
	if (r2 != nullptr) {
		m_contactNormal = (m_rigidbodies[0]->GetPosition() - m_rigidbodies[1]->GetPosition()).normalize();
	}
	else {
		m_contactNormal = Vector3D(0, 1, 0);
	}
}

void Contact::resolve(float duration)
{
	//resolveVelocity();
	//resolveInterpretation();
}

float Contact::calculateSeperatingVelocity()
{
	if (m_rigidbodies[1] != nullptr)
		return Vector3D::scalarProduct((m_rigidbodies[0]->GetVelocity() - m_rigidbodies[1]->GetVelocity()), m_contactNormal);
	else
		return Vector3D::scalarProduct(m_rigidbodies[0]->GetVelocity(), m_contactNormal);
}
