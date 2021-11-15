#include "Rigidbody.h"

void Rigidbody::Integrate(float duration)
{
	//Acceleration
	Vector3D linearAcceleration = m_inverseMass * m_forceAccum;
	Vector3D angularAcceleration = m_inverseTenseurInertieWorld * m_torqueAccum;
	
	//Vitesse
	m_velocity = m_velocity * pow(m_damping, duration) + linearAcceleration * duration;
	m_rotation = m_rotation * pow(m_angularDamping, duration) + angularAcceleration * duration;

	//Position
	m_position = m_position + m_velocity * duration;
	m_orientation.UpdateByAngularVelocity(m_rotation, duration);

	//Update datas
	CalculateDerivedData();
	ClearAccumulator();
}

void Rigidbody::AddForce(const Vector3D& force)
{
	m_forceAccum += force;
}

void Rigidbody::AddForceAtPoint(const Vector3D& force, const Vector3D& worldPoint)
{
	AddForce(force);
	m_torqueAccum += (m_position - worldPoint) * force;
}

void Rigidbody::AddForceAtBodyPoint(const Vector3D& force, const Vector3D& localPoint)
{
	Vector3D world = LocalToWorld(localPoint);
	AddForceAtPoint(force, world);
}

void Rigidbody::ClearAccumulator()
{
	m_forceAccum = Vector3D(0, 0, 0);
	m_torqueAccum = Vector3D(0, 0, 0);
}

void Rigidbody::SetInertiaTenseur(const Matrix33& tenseurInertie)
{
	m_inverseTenseurInertie = tenseurInertie.Inverse();
}

void Rigidbody::CalculateDerivedData()
{
	m_transformMatrix.SetOrientationAndPosition(m_orientation, m_position);
	ComputeTenseurInertiaWorld(m_inverseTenseurInertieWorld);
}

void Rigidbody::ComputeTenseurInertiaWorld(Matrix33& inertiaTenseurWorld)
{
	inertiaTenseurWorld = m_transformMatrix * m_inverseTenseurInertie;
}

Vector3D Rigidbody::LocalToWorld(const Vector3D& local)
{
	return m_transformMatrix.Inverse()*local;
}

Vector3D Rigidbody::WorldToLocal(const Vector3D& world)
{

	return m_transformMatrix * world;
}