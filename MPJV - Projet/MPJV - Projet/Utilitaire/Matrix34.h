#pragma once
#include "../Vector3D.h"
#include "Quaternion.h"

class Matrix34 {
private:
	float m_values[12];

public:

	//Constructor
	Matrix34() = default;
	Matrix34(float values[12]);
	Matrix34(const Matrix34& other);

	//Destructor
	~Matrix34() = default;

	//Accessors
	float getValueAt(int i, int j);

	//Operators
	Matrix34 operator*(const Matrix34& other) const;

	Vector3D operator*(const Vector3D& other) const;

	//Methods
	Matrix34 Inverse();

	Matrix34 Transpose();

	void SetOrientationAndPosition(const Quaternion& q);

	static float Determinant(const Matrix34& mat);

};