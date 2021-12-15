#pragma once
#include "../Vector3D.h"
#include "Quaternion.h"

class Matrix33 {
private:
	float m_values[9];

public:

	//Constructor
	Matrix33() : m_values{ 1, 0, 0,
						   0, 1, 0,
						   0, 0, 1} {}
	Matrix33(float values[9]);
	Matrix33(const Matrix33& other);

	//Destructor
	~Matrix33() = default;

	//Accessors
	float getValueAt(int i, int j) const;

	//Operators
	Matrix33& operator*=(const Matrix33& other);
	friend Matrix33 operator*(const Matrix33& m1, const Matrix33& m2);

	Matrix33& operator*=(const float& other);
	friend Matrix33 operator*(const Matrix33& m1, const float& f1);

	friend Vector3D operator*(const Matrix33& m1, const Vector3D& v1);

	//Methods
	Matrix33 Inverse() const;

	Matrix33 Transpose();

	void rotate(const Quaternion& rotation);

	Quaternion getRotation() const;

	void SetRotation(const Quaternion& q);

	static float Determinant(const Matrix33& mat);

};