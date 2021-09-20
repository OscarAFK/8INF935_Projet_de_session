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

public:
	//Constructors
	Particle(float invertedMass = 0.0f, float damping = 0.0f, Vector3D position = Vector3D(), Vector3D velocity = Vector3D(), Vector3D acceleration = Vector3D());
	~Particle();

	//Accessors
	float getInvertedMass() const;
	float getMass() const;
	float getDamping() const;
	Vector3D getPosition() const;
	Vector3D getVelocity() const;
	Vector3D getAcceleration() const;

	//Mutators
	void setInvertedMass(const float value);
	void setMass(const float value);
	void setDamping(const float value);
	void setPosition(const Vector3D value);
	void setVelocity(const Vector3D value);
	void setAcceleration(const Vector3D value);

	//Methods
	void integrate(float deltaTime);

	//Operators
	bool operator==(const Particle v);

	//Utils
	std::string to_string() const;
};