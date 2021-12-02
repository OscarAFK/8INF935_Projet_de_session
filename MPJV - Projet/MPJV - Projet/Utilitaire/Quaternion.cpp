#include "Quaternion.h"

#pragma region Constructors
Quaternion::Quaternion(float w, float i, float j, float k) : m_values{ w,i,j,k }
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
    float i = m_values[0] * other.m_values[1] + m_values[1] * other.m_values[0] + m_values[2] * other.m_values[3] - m_values[3] * other.m_values[2];
    float j = m_values[0] * other.m_values[2] + m_values[2] * other.m_values[0] + m_values[3] * other.m_values[1] - m_values[1] * other.m_values[3];
    float k = m_values[0] * other.m_values[3] + m_values[3] * other.m_values[0] + m_values[1] * other.m_values[2] - m_values[2] * other.m_values[1];
    m_values[0] = m_values[0] * other.m_values[0] - m_values[1] * other.m_values[1] - m_values[2] * other.m_values[2] - m_values[3] * other.m_values[3];
    m_values[1] = i;
    m_values[2] = j;
    m_values[3] = k;
    
    //Normalize();
    return (*this);
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
    float magnitude = sqrt(m_values[0] * m_values[0] + m_values[1] * m_values[1] + m_values[2] * m_values[2] + m_values[3] * m_values[3]);
    m_values[0] = m_values[0] / magnitude;
    m_values[1] = m_values[1] / magnitude;
    m_values[2] = m_values[2] / magnitude;
    m_values[3] = m_values[3] / magnitude;
}

void Quaternion::RotateByVector(const Vector3D& vector)
{
    if (vector.norm() == 0) return;
    Quaternion q = Quaternion(0, vector.getX(), vector.getY(), vector.getZ());
    (*this) *= q;
    Normalize();
}

void Quaternion::UpdateByAngularVelocity(const Vector3D& rotation, float duration)
{
    if (rotation.norm() == 0) return;
    Quaternion q = Quaternion(0, rotation.getX(), rotation.getY(), rotation.getZ());
    q *= (*this);
    m_values[0] += q.getW() * 0.5f * duration;
    m_values[1] += q.getI() * 0.5f * duration;
    m_values[2] += q.getJ() * 0.5f * duration;
    m_values[3] += q.getK() * 0.5f * duration;
    Normalize();
}

//J'ai utilisé le code fournit sur cette page: https://en.wikipedia.org/wiki/Conversion_between_quaternions_and_Euler_angles
Vector3D Quaternion::ToEuler()
{
    Vector3D angles;

    // roll (x-axis rotation)
    float sinr_cosp = 2 * (m_values[0] * m_values[1] + m_values[2] * m_values[3]);
    float cosr_cosp = 1 - 2 * (m_values[1] * m_values[1] + m_values[2] * m_values[2]);
    angles.setX(std::atan2(sinr_cosp, cosr_cosp));

    // pitch (y-axis rotation)
    float sinp = 2 * (m_values[0] * m_values[2] - m_values[3] * m_values[1]);
    if (std::abs(sinp) >= 1)
        angles.setY(std::copysign(M_PI / 2, sinp)); // use 90 degrees if out of range
    else
        angles.setY(std::asin(sinp));

    // yaw (z-axis rotation)
    float siny_cosp = 2 * (m_values[0] * m_values[3] + m_values[1] * m_values[2]);
    float cosy_cosp = 1 - 2 * (m_values[2] * m_values[2] + m_values[3] * m_values[3]);
    angles.setZ(std::atan2(siny_cosp, cosy_cosp));
    return angles;
}

//Idem
void Quaternion::SetByEulerRotation(Vector3D euler)
{
    // Abbreviations for the various angular functions
    double cy = cos(euler.getZ() * 0.5);
    double sy = sin(euler.getZ() * 0.5);
    double cp = cos(euler.getY() * 0.5);
    double sp = sin(euler.getY() * 0.5);
    double cr = cos(euler.getX() * 0.5);
    double sr = sin(euler.getX() * 0.5);

    m_values[0] = cr * cp * cy + sr * sp * sy;
    m_values[1] = sr * cp * cy - cr * sp * sy;
    m_values[2] = cr * sp * cy + sr * cp * sy;
    m_values[3] = cr * cp * sy - sr * sp * cy;
}

#pragma endregion
