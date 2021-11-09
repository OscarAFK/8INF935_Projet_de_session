#pragma once
#include "../Vector3D.h"
#include "Quaternion.h"
#include "Matrix34.h"

class Rigidbody {
private:
	//same as for particle
	float m_inverseMass;
	float m_damping;
	Vector3D m_velocity;
	Vector3D m_position;

	// orientation of the rigidbody
	Quaternion m_orientation;

	//angular velocity of the rigidbody
	Vector3D m_rotation;

	//Calculates transform matrix from rotation and rotation
	Matrix34 m_transformMatrix;

	//same as linear damping but for rotation
	float m_angularDamping;

	//Accumulated force added by ForceGenerator
	Vector3D m_forceAccum;

	//Accumulated torque added by ForceGenerator
	Vector3D m_torqueAccum;

public:

	//Integrate the rigidbody by modifying position, orientation and velocities
	void Integrate(float duration);

	//Add force on the center of mass --> no torque
	void AddForce(const Vector3D &force);

	//Add force to a point in world coordinate --> torque
	void AddForceAtPoint(const Vector3D& force,	const Vector3D& worldPoint);

	//Add force at point in local coordinate --> torque
	void AddForceAtBodyPoint(const Vector3D& force, const Vector3D& localPoint);

	//called each frame, reset m_forceAccum and m_torqueAccum
	void ClearAccumulator();

private:

	//call each frame to calculate the transform matrix and normalize the rotation
	void CalculateDerivedData();

	//
	Vector3D LocalToWorld(const Vector3D& local);
	Vector3D WorldToLocal(const Vector3D& world);
};