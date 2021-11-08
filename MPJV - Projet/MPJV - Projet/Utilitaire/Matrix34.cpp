#include "Matrix34.h"

Matrix34::Matrix34(float values[12])
{
    for (int i = 0; i < 12; i++) {
        m_values[i] = values[i];
    }
}

Matrix34::Matrix34(const Matrix34& other)
{
    for (int i = 0; i < 12; i++) {
        m_values[i] = other.m_values[i];
    }
}

Matrix34::Matrix34(const Matrix33& mat33, const Vector3D& vect)
{
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            m_values[i + j * 4] = mat33.getValueAt(i,j);
        }
    }
    auto valuesVect = vect.getValues();
    for (int i = 0; i < 3; i++) {
        m_values[3 + i * 4] = valuesVect[i];
    }
}

float Matrix34::getValueAt(int i, int j) const
{
    return m_values[i + j * 4];
}

Matrix34& Matrix34::operator*=(const Matrix34& other)
{
    Matrix34 newMat = Matrix34();
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++) {
            newMat.m_values[i + j * 3] = 0;
            for (int k = 0; k < 3; k++)
                newMat.m_values[i + j * 4] += m_values[k + i * 4] * other.m_values[j + k * 4];
        }
    for (int i = 0; i < 3; i++) {
        newMat.m_values[3 + i * 4] = other.m_values[3 + i * 4];
    }
    return newMat;
}

Matrix34& Matrix34::operator*=(const float& other)
{
    Matrix34 newMat = Matrix34();
    for (int i = 0; i < 12; i++)
        newMat.m_values[i] = m_values[i] * other;
    return newMat;
}

Matrix34 operator*(const Matrix34& m1, const Matrix34& m2)
{
    auto m3 = m1;
    m3 *= m2;
    return m3;
}

Matrix34 operator*(const Matrix34& m1, const float& f1)
{
    Matrix34 m2 = m1;
    m2 *= f1;
    return m2;
}

Vector3D operator*(const Matrix34& m1, const Vector3D& v1)
{
    Vector3D newVec = Vector3D();
    auto vecValues = v1.getValues();
    vecValues.emplace_back(0);              //Je pense que c'est 0, mais c'est peut-être 1
    for (int i = 0; i < 3; i++) {
        float val = 0;
        for (int j = 0; j < 4; j++)
            val += vecValues[j] * m1.m_values[j + i * 4];
        if (i == 0) newVec.setX(val);
        else if (i == 1) newVec.setY(val);
        else if (i == 2) newVec.setZ(val);
    }
    return newVec;
}

Matrix34 Matrix34::Inverse()
{
    float valuesSousMat[9] = { m_values[0] , m_values[1], m_values[2], m_values[3], m_values[4], m_values[5], m_values[6], m_values[7], m_values[8] };
    Matrix33 sousMat = Matrix33(valuesSousMat).Inverse();
    float valuesVector[3] = { m_values[3], m_values[7], m_values[11] };
    Vector3D sousVect = sousMat*Vector3D(valuesVector)*(-1);
    return Matrix34(sousMat, sousVect);
}

void Matrix34::SetOrientationAndPosition(const Quaternion& q, const Vector3D& p)
{
    m_values[0] = 1 - (2 * q.getJ() * q.getJ() + 2 * q.getK() * q.getK());
    m_values[1] = 2 * q.getI() * q.getJ() + 2 * q.getK() * q.getW();
    m_values[2] = 2 * q.getI() * q.getK() - 2 * q.getJ() * q.getW();
    m_values[3] = p.getX();
    m_values[4] = 2 * q.getI() * q.getJ() - 2 * q.getK() * q.getW();
    m_values[5] = 1 - (2 * q.getI() * q.getI() + 2 * q.getK() * q.getK());
    m_values[6] = 2 * q.getJ() * q.getK() + 2 * q.getI() * q.getW();
    m_values[7] = p.getY();
    m_values[8] = 2 * q.getI() * q.getK() + 2 * q.getJ() * q.getW();
    m_values[9] = 2 * q.getJ() * q.getK() - 2 * q.getI() * q.getW();
    m_values[10] = 1 - (2 * q.getI() * q.getI() + 2 * q.getJ() * q.getJ());
    m_values[11] = p.getZ();
}

Vector3D Matrix34::TransformPosition(const Vector3D& vector)
{
    auto valuesVec = vector.getValues();
    float vectReturn[3] = {0,0,0};
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            vectReturn[i] += valuesVec[j] * m_values[j + i * 4];
        }
    }
    return Vector3D(vectReturn);
}

Vector3D Matrix34::TransformDirection(const Vector3D& vector)
{
    auto valuesVec = vector.getValues();
    float vectReturn[3] = { 0,0,0 };
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            vectReturn[i] += valuesVec[j] * m_values[i + j * 4];
        }
    }
    return Vector3D(vectReturn);
}
