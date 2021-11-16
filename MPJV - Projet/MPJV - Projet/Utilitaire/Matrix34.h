#pragma once
#include "../Vector3D.h"
#include "Quaternion.h"
#include "Matrix33.h"

class Matrix34 {
private:
	float m_values[12];

public:

	//Constructor
	Matrix34() = default;
	Matrix34(float values[12]);
	Matrix34(const Matrix34& other);
	Matrix34(const Matrix33& mat33, const Vector3D& vect);

	//Destructor
	~Matrix34() = default;

	//Accessors
	float getValueAt(int i, int j) const;

	//Operators
	Matrix34& operator*=(const Matrix34& other);
	friend Matrix34 operator*(const Matrix34& m1, const Matrix34& m2);

	Matrix34& operator*=(const float& other);
	friend Matrix34 operator*(const Matrix34& m1, const float& f1);

	friend Vector3D operator*(const Matrix34& m1, const Vector3D& v1);

	//Methods

	// Return the Inverse Matrix. It is supposed that the matrix is always affine
	Matrix34 Inverse();

	// Set the matrix base on a quaternion and position
	void SetOrientationAndPosition(const Quaternion& q, const Vector3D& p);

	//Transform a position
	Vector3D TransformPosition(const Vector3D& vector);

	//Transform a direction by ignoring the translation
	Vector3D TransformDirection(const Vector3D& vector);

	Matrix33 ToMatrix33() const;


};