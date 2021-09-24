#include "Particle.h"

#pragma region Constructors

Particle::Particle(float invertedMass, float damping, Vector3D position, Vector3D velocity, Vector3D acceleration) :
	m_inverseMass(invertedMass), m_damping(damping), m_position(position), m_velocity(velocity), m_acceleration(acceleration)
{
}

Particle::~Particle() {}

#pragma endregion

#pragma region Accessors

float Particle::getInvertedMass() const
{
	return m_inverseMass;
}

float Particle::getMass() const
{
	return 1/m_inverseMass;
}

float Particle::getDamping() const
{
	return m_damping;
}

Vector3D Particle::getPosition() const
{
	return m_position;
}

Vector3D Particle::getVelocity() const
{
	return m_velocity;
}

Vector3D Particle::getAcceleration() const
{
	return m_acceleration;
}

#pragma endregion

#pragma region Mutators

void Particle::setInvertedMass(const float value)
{
	m_inverseMass = value;
}

void Particle::setMass(const float value)
{
	m_inverseMass = 1/value;
}

void Particle::setDamping(const float value)
{
	m_damping = value;
}

void Particle::setPosition(const Vector3D value)
{
	m_position = value;
}

void Particle::setVelocity(const Vector3D value)
{
	m_velocity = value;
}

void Particle::setAcceleration(const Vector3D value)
{
	m_acceleration = value;
}

#pragma endregion

#pragma region Methods
void Particle::integrate(float deltaTime)
{
	m_position = m_position + m_velocity * deltaTime + 0.5 * m_acceleration * deltaTime * deltaTime;
	m_velocity = m_velocity * m_damping + m_acceleration * deltaTime;
}

#pragma endregion

#pragma region Operators

bool Particle::operator==(const Particle v)
{
	if (m_inverseMass == v.m_inverseMass && m_acceleration == v.m_acceleration && m_velocity == v.m_velocity && m_position == v.m_position)
	{
		return true;
	}
	return false;
}

#pragma endregion

#pragma region Utils

std::string Particle::to_string() const
{
	char string[256];
	sprintf_s(string, "Mass : %f\nPosition%s\nVelocity%s\nAcceleration%s\n", 1/m_inverseMass,
																					  m_position.to_string().c_str(),
																					  m_velocity.to_string().c_str(),
																					  m_acceleration.to_string().c_str());
	return string;
}

#pragma endregion