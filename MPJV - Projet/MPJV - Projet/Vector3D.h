#pragma once

#ifndef VECTOR3D_H
#define VECTOR3D_H

#include <cmath>
#include <string>

class Vector3D
{
	private:
		float m_x, m_y, m_z;

	public:
		Vector3D(float x = 0, float y = 0, float z = 0);
		~Vector3D() = default;

		float getX() const;
		float getY() const;
		float getZ() const;

		void setX(const float value);
		void setY(const float value);
		void setZ(const float value);

		Vector3D normalize();

		static float scalarProduct(Vector3D v1, Vector3D v2);
		static Vector3D dotProduct(Vector3D v1, Vector3D v2);

		bool operator==(const Vector3D v);

		Vector3D& operator+=(const Vector3D& v);
		friend Vector3D operator+(Vector3D v1, const Vector3D& v2);

		Vector3D& operator-=(const Vector3D& v);
		friend Vector3D operator-(Vector3D v1, const Vector3D& v2);

		Vector3D& operator*=(const float& v);
		friend Vector3D operator*(Vector3D v1, const float& v2);
		friend Vector3D operator*(const float& v1, Vector3D v2);

		Vector3D& operator/=(const float& v);
		friend Vector3D operator/(Vector3D v1, const float& v2);

		std::string to_string() const;
};
#endif