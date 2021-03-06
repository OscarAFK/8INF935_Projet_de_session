#include "Vector3D.h"

#pragma region Constructors

Vector3D::Vector3D(float x, float y, float z) :
	m_x(x), m_y(y), m_z(z)
{ }

#pragma endregion

#pragma region Accessors

float Vector3D::getX() const
{
	return m_x;
}

float Vector3D::getY() const
{
	return m_y;
}

float Vector3D::getZ() const
{
	return m_z;
}

#pragma endregion

#pragma region Mutators

void Vector3D::setX(float value)
{
	m_x = value;
}

void Vector3D::setY(float value)
{
	m_y = value;
}

void Vector3D::setZ(float value)
{
	m_z = value;
}

#pragma endregion

#pragma region Methods

Vector3D Vector3D::normalize()
{
	float norm = sqrt(m_x * m_x + m_y * m_y + m_z * m_z);
	return Vector3D(m_x / norm, m_y / norm, m_z / norm);
}

float Vector3D::scalarProduct(Vector3D v1, Vector3D v2)
{
	return v1.m_x * v2.m_x + v1.m_y * v2.m_y + v1.m_z * v2.m_z;
}

Vector3D Vector3D::dotProduct(Vector3D v1, Vector3D v2)
{
	return Vector3D(v1.m_y * v2.m_z - v1.m_z * v2.m_y,
		v1.m_z * v2.m_x - v1.m_x * v2.m_z,
		v1.m_x * v2.m_y - v1.m_y * v2.m_x);
}

#pragma endregion

#pragma region Operators

bool Vector3D::operator==(const Vector3D v)
{
	if (m_x == v.m_x && m_y == v.m_y && m_z == v.m_z)
	{
		return true;
	}
	return false;
}

Vector3D& Vector3D::operator+=(const Vector3D& v)
{
	m_x += v.m_x;
	m_y += v.m_y;
	m_z += v.m_z;
	return *this;
}

Vector3D operator+(Vector3D v1, const Vector3D& v2)
{
	v1 += v2;
	return v1;
}

Vector3D& Vector3D::operator-=(const Vector3D& v)
{
	m_x -= v.m_x;
	m_y -= v.m_y;
	m_z -= v.m_z;
	return *this;
}

Vector3D operator-(Vector3D v1, const Vector3D& v2)
{
	v1 -= v2;
	return v1;
}

Vector3D& Vector3D::operator*=(const float& value)
{
	m_x *= value;
	m_y *= value;
	m_z *= value;
	return *this;
}

Vector3D operator*(Vector3D vector, const float& value)
{
	vector *= value;
	return vector;
}

Vector3D operator*(const float& value, Vector3D vector)
{
	vector *= value;
	return vector;
}

Vector3D& Vector3D::operator/=(const float& value)
{
	m_x /= value;
	m_y /= value;
	m_z /= value;
	return *this;
}

Vector3D operator/(Vector3D vector, const float& value)
{
	vector /= value;
	return vector;
}

#pragma endregion

#pragma region Utils

std::string Vector3D::to_string() const
{
	char string[64];
	sprintf_s(string, "(%f, %f, %f)", m_x, m_y, m_z);
	return string;
}

#pragma endregion