#pragma once

#include "Vector3D.h"

class Particle
{
private:

	float m_inverseMass;
	float m_damping;
	Vector3D m_acceleration;
	Vector3D m_velocity;
	Vector3D m_position;
	Vector3D m_forces;

public:
	//Constructors
	Particle(float inverseMass = 0.0f, float damping = 0.0f, Vector3D position = Vector3D(), Vector3D velocity = Vector3D(), Vector3D acceleration = Vector3D());
	~Particle();

	//Accessors
	float getInverseMass() const;
	float getMass() const;
	float getDamping() const;
	Vector3D getPosition() const;
	Vector3D getVelocity() const;
	Vector3D getAcceleration() const;
	Vector3D getForces() const;

	//Mutators
	void setInverseMass(const float value);
	void setMass(const float value);
	void setDamping(const float value);
	void setPosition(const Vector3D value);
	void setVelocity(const Vector3D value);
	void setAcceleration(const Vector3D value);
	void setForces(const Vector3D value);

	//Methods
	void integrate(float deltaTime);
	void addForce(const Vector3D value);

	//Operators
	bool operator==(const Particle v);

	//Utils
	std::string to_string() const;
};