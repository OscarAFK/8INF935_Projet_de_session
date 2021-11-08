#include "Quaternion.h"

#pragma region Constructors
Quaternion::Quaternion(float w, float i, float j, float k) : m_values {w,i,j,k}{}

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

Quaternion Quaternion::operator*(const Quaternion& other)
{
    /*float w = m_w*other.m_w - m_i * other.m_i - m_j * other.m_j - m_k * other.m_k;
    float i = m_w * other.m_i + m_i * 
    float j = 
    float k = */
    return Quaternion();
}

#pragma endregion

#pragma region Methods

void Quaternion::Normalize()
{
}

void Quaternion::RotateByVector(const Vector3D& vector)
{
}

void Quaternion::UpdateByAngularVelocity(const Vector3D& rotation, float duration)
{
}

#pragma endregion