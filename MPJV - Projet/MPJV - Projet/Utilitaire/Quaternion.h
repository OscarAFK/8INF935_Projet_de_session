#pragma once
#include "../Vector3D.h"
#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>

class Quaternion {
private:
	float m_values[4];

public:
	//Constructor
	Quaternion() = default;
	Quaternion(float w, float i, float j, float k);
	Quaternion(const Quaternion& other);

	//Destructor
	~Quaternion() = default;

	//Accessors
	float getW() const;
	float getI() const;
	float getJ() const;
	float getK() const;

	//Operators
	Quaternion operator*=(const Quaternion& other);
	friend Quaternion operator*(const Quaternion& q1, const Quaternion& q2);

	//Methods
	void Normalize();

	void RotateByVector(const Vector3D& vector);

	void UpdateByAngularVelocity(const Vector3D& rotation, float duration);

	Vector3D ToEuler();

};