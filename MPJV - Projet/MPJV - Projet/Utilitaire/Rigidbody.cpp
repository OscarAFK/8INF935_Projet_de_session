#include "Rigidbody.h"

void Rigidbody::Integrate(float duration)
{

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

void Rigidbody::CalculateDerivedData()
{
	m_transformMatrix.SetOrientationAndPosition(m_orientation, m_position);
}

Vector3D Rigidbody::LocalToWorld(const Vector3D& local)
{
	return m_transformMatrix.Inverse()*local;
}

Vector3D Rigidbody::WorldToLocal(const Vector3D& world)
{

	return m_transformMatrix * world;
}