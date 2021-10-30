#pragma once
#include "../Vector3D.h"

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
	const float getW();
	const float getI();
	const float getJ();
	const float getK();

	//Operators
	Quaternion operator*(const Quaternion& other);

	//Methods
	void Normalize();

	void RotateByVector(const Vector3D& vector);

	void UpdateByAngularVelocity(const Vector3D& rotation, float duration);

};