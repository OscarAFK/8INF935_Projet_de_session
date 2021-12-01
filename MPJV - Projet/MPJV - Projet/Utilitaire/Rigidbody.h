#pragma once
#include "../Vector3D.h"
#include "Quaternion.h"
#include "../Component.h"
#include "Matrix34.h"
#include <iostream>
#include "../Entity.h"

class Rigidbody : public Component{
private:
	//same as for particle
	float m_inverseMass;
	float m_damping;
	Vector3D m_velocity;
	Vector3D m_position;
	Vector3D m_previousPos;

	// orientation of the rigidbody
	Quaternion m_orientation;

	//angular velocity of the rigidbody
	Vector3D m_rotation;

	//Calculates transform matrix from rotation and rotation
	Matrix34 m_transformMatrix;

	//Calculates tenseur of inertia
	Matrix33 m_inverseTenseurInertie;
	Matrix33 m_inverseTenseurInertieWorld;

	//same as linear damping but for rotation
	float m_angularDamping;

	//Accumulated force added by ForceGenerator
	Vector3D m_forceAccum;

	//Accumulated torque added by ForceGenerator
	Vector3D m_torqueAccum;

public:

	Rigidbody(Entity* owner);
	//Rigidbody(Vector3D position, Quaternion orientation, float mass, float damping, float angularDamping, Matrix33 tenseurInertie);
	//Rigidbody(Vector3D position = Vector3D());

	void Initialize(float mass, float damping, float angularDamping, Matrix33 tenseurInertie);

	//Integrate the rigidbody by modifying position, orientation and velocities
	void Integrate(float duration);

	//Add force on the center of mass --> no torque
	void AddForce(const Vector3D& force);

	//Add force to a point in world coordinate --> torque
	void AddForceAtPoint(const Vector3D& force, const Vector3D& worldPoint);

	//Add force at point in local coordinate --> torque
	void AddForceAtBodyPoint(const Vector3D& force, const Vector3D& localPoint);

	//called each frame, reset m_forceAccum and m_torqueAccum
	void ClearAccumulator();

	void SetInertiaTenseur(const Matrix33& tenseurInertie);

	float GetMass() const;

	Vector3D GetPosition() const;
	Vector3D GetPreviousPosition() const;

	void renderComponentUI();

private:

	//call each frame to calculate the transform matrix and normalize the rotation
	void CalculateDerivedData();

	void ComputeTenseurInertiaWorld(Matrix33& inertiaTenseur);

	//
	Vector3D LocalToWorld(const Vector3D& local);
	Vector3D WorldToLocal(const Vector3D& world);
};

namespace tenseursFormesDeBase {
	Matrix33 Sphere(float m, float r);

	Matrix33 Cuboide(float m, Vector3D d);

	Matrix33 Cylindre(float m, float r, float h);
};

float getRandomValue(float min, float max);