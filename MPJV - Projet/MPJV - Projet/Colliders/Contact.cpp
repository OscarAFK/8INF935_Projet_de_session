#include "Contact.h"

Contact::Contact(Rigidbody* r1, Rigidbody* r2, float restitution, float penetration) :
												m_restitution(restitution), m_penetration(penetration)
{
	m_rigidbodies[0] = r1;
	m_rigidbodies[1] = r2;
	if (r2 != nullptr) {
		m_contactNormal = (m_rigidbodies[0]->getOwner()->transform->getPosition() - m_rigidbodies[1]->getOwner()->transform->getPosition()).normalize();
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

float Contact::calculateSeperatingVelocity() const
{
	if (m_rigidbodies[1] != nullptr)
		return Vector3D::scalarProduct((m_rigidbodies[0]->GetVelocity() - m_rigidbodies[1]->GetVelocity()), m_contactNormal);
	else
		return Vector3D::scalarProduct(m_rigidbodies[0]->GetVelocity(), m_contactNormal);
}

void Contact::printInfoContact() const
{
	std::cout << "\t---Contact detecté---" << std::endl
		<< "------------------" << std::endl
		<< "Nom de l'objet 1: " << m_rigidbodies[0]->getOwner()->getName() << std::endl
		<< "Nom de l'objet 2: " << m_rigidbodies[1]->getOwner()->getName() << std::endl
		<< "Point de contact: " << m_contactPoint.to_string() << std::endl
		<< "Normale du contact: " << m_contactNormal.to_string() << std::endl
		<< "Vitesse de séparation: " << calculateSeperatingVelocity() << std::endl
		<< "Penetration: " << m_penetration << std::endl
		<< "Restitution: " << m_restitution << std::endl << std::endl;
}
