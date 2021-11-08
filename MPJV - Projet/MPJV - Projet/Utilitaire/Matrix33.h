#pragma once
#include "../Vector3D.h"
#include "Quaternion.h"

class Matrix33 {
private:
	float m_values[9];

public:

	//Constructor
	Matrix33() = default;
	Matrix33(float values[9]);
	Matrix33(const Matrix33& other);

	//Destructor
	~Matrix33() = default;

	//Accessors
	float getValueAt(int i, int j);

	//Operators
	Matrix33& operator*=(const Matrix33& other);
	friend Matrix33 operator*(const Matrix33& m1, const Matrix33& m2);

	Matrix33& operator*=(const float& other);
	friend Matrix33 operator*(const Matrix33& m1, const float& f1);

	Matrix33& operator*=(const Vector3D& other);
	friend Matrix33 operator*(const Matrix33& m1, const Vector3D& v1);

	//Methods
	Matrix33 Inverse();

	Matrix33 Transpose();

	void SetOrientation(const Quaternion& q);

	static float Determinant(const Matrix33& mat);

};