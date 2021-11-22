#include "Rigidbody.h"

Rigidbody::Rigidbody(Vector3D position, Quaternion orientation, float mass, float damping, float angularDamping, Matrix33 tenseurInertie) : 
	m_position(position), m_orientation(orientation), m_inverseMass(1/mass), m_damping(damping), m_angularDamping(angularDamping),
	m_forceAccum(Vector3D(0,0,0)), m_torqueAccum(Vector3D(0,0,0))
{
	CalculateDerivedData();
	SetInertiaTenseur(tenseurInertie);
}

void Rigidbody::Integrate(float duration)
{
	//Acceleration
	Vector3D linearAcceleration = m_inverseMass * m_forceAccum;
	Vector3D angularAcceleration = m_inverseTenseurInertieWorld * m_torqueAccum;
	
	//Vitesse
	m_velocity = m_velocity * pow(m_damping, duration) + linearAcceleration * duration;
	m_rotation = m_rotation * pow(m_angularDamping, duration) + angularAcceleration * duration;

	//Position
	m_previousPos = m_position;
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

float Rigidbody::GetMass() const
{
	if (m_inverseMass != 0) return 1 / m_inverseMass;
	std::cout << "ERROR: infinite mass" << std::endl;
	return -1;
}

Vector3D Rigidbody::GetPosition() const
{
	return m_position;
}

Vector3D Rigidbody::GetPreviousPosition() const
{
	return m_previousPos;
}

void Rigidbody::CalculateDerivedData()
{
	m_transformMatrix.SetOrientationAndPosition(m_orientation, m_position);
	ComputeTenseurInertiaWorld(m_inverseTenseurInertieWorld);
}

void Rigidbody::ComputeTenseurInertiaWorld(Matrix33& inertiaTenseurWorld)
{
	Matrix33 transformMatrix33 = m_transformMatrix.ToMatrix33();
	inertiaTenseurWorld = transformMatrix33 * m_inverseTenseurInertie;
	inertiaTenseurWorld *= transformMatrix33.Inverse();
}

Vector3D Rigidbody::LocalToWorld(const Vector3D& local)
{
	return m_transformMatrix.Inverse()*local;
}

Vector3D Rigidbody::WorldToLocal(const Vector3D& world)
{
	return m_transformMatrix * world;
}

Matrix33 tenseursFormesDeBase::Sphere(float m, float r) {
	float values[] = { 2 / 5.0f * m * r * r, 0,0,
						0,2 / 5.0f * m * r * r, 0,
						0,0,2 / 5.0f * m * r * r };
	return Matrix33(values);
}

Matrix33 tenseursFormesDeBase::Cuboide(float m, Vector3D d) {
	float values[] = { 1 / 12.0f * m * (d.getY() * d.getY() + d.getZ() * d.getZ()), 0,0,
						0,1 / 12.0f * m * (d.getX() * d.getX() + d.getZ() * d.getZ()), 0,
						0,0,1 / 12.0f * m * (d.getY() * d.getY() + d.getX() * d.getX()) };
	return Matrix33(values);
}

Matrix33 tenseursFormesDeBase::Cylindre(float m, float r, float h) {
	float values[] = { 1 / 12.0f * m * h * h + 1 / 4.0f * m * r * r, 0,0,
						0,1 / 2.0f * m * r * r, 0,
						0,0,1 / 12.0f * m * h * h + 1 / 4.0f * m * r * r };
	return Matrix33(values);
}
