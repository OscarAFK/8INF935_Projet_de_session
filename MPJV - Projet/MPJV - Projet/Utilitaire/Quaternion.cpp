#include "Quaternion.h"

#pragma region Constructors
Quaternion::Quaternion(float w, float i, float j, float k) : m_values {w,i,j,k}
{
}

Quaternion::Quaternion(const Quaternion& other) : 
    m_values{ other.m_values[0], other.m_values[1], other.m_values[2], other.m_values[3] }
{}

#pragma endregion

#pragma region Accessors

float Quaternion::getW() const
{
    return m_values[0];
}

float Quaternion::getI() const
{
    return m_values[1];
}

float Quaternion::getJ() const
{
    return m_values[2];
}

float Quaternion::getK() const
{
    return m_values[3];
}

#pragma endregion

#pragma region Operators

Quaternion Quaternion::operator*=(const Quaternion& other)
{
    float w = m_values[0] * other.m_values[0] - m_values[1] * other.m_values[1] - m_values[2] * other.m_values[2] - m_values[3] * other.m_values[3];
    float i = m_values[0] * other.m_values[1] + m_values[1] * other.m_values[0] + m_values[2] * other.m_values[3] - m_values[3] * other.m_values[2];
    float j = m_values[0] * other.m_values[2] + m_values[2] * other.m_values[0] + m_values[3] * other.m_values[1] - m_values[1] * other.m_values[3];
    float k = m_values[0] * other.m_values[3] + m_values[3] * other.m_values[0] + m_values[1] * other.m_values[2] - m_values[2] * other.m_values[1];
    Quaternion returnValue = Quaternion(w, i, j, k);
    returnValue.Normalize();
    return returnValue;
}

Quaternion operator*(const Quaternion& q1, const Quaternion& q2)
{
    Quaternion q3 = q1;
    q3 *= q2;
    return q3;
}

#pragma endregion

#pragma region Methods

void Quaternion::Normalize()
{
    float magnitude = sqrt(m_values[0]* m_values[0]+ m_values[1]* m_values[1]+ m_values[2]* m_values[2]+ m_values[3]* m_values[3]);
    m_values[0] = m_values[0]/magnitude;
    m_values[1] = m_values[1]/magnitude;
    m_values[2] = m_values[2]/magnitude;
    m_values[3] = m_values[3]/magnitude;
}

void Quaternion::RotateByVector(Vector3D& vector)
{
    Quaternion q = Quaternion(0, *vector.getX(), *vector.getY(), *vector.getZ());
    (*this) *= q;
    Normalize();
}

void Quaternion::UpdateByAngularVelocity(Vector3D& rotation, float duration)
{
    Quaternion q = Quaternion(0, *rotation.getX(), *rotation.getY(), *rotation.getZ());
    q *= (*this);
    m_values[0] += q.getW() * 0.5f;
    m_values[1] += q.getI() * 0.5f;
    m_values[2] += q.getJ() * 0.5f;
    m_values[3] += q.getK() * 0.5f;
    Normalize();
}

#pragma endregion
