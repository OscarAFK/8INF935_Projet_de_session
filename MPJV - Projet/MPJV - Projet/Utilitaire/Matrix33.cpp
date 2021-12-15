#include "Matrix33.h"

#pragma region Constructors

Matrix33::Matrix33(float values[9])
{
    for (int i = 0; i < 9; i++) {
        m_values[i] = values[i];
    }
}

Matrix33::Matrix33(const Matrix33& other)
{
    for (int i = 0; i < 9; i++) {
        m_values[i] = other.m_values[i];
    }
}

#pragma endregion

#pragma region Accessors
float Matrix33::getValueAt(int i, int j) const
{
    return m_values[i + j*3];
}

#pragma endregion

#pragma region Operators

Matrix33& Matrix33::operator*=(const Matrix33& other)
{
    Matrix33 newMat = Matrix33();
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++) {
            newMat.m_values[i + j * 3] = 0;
            for (int k = 0; k < 3; k++)
                newMat.m_values[i + j * 3] += m_values[k + i * 3] * other.m_values[j + k * 3];
        }
    for (int i = 0; i < 9; i++) {
        m_values[i] = newMat.m_values[i];
    }
    return (*this);
}

Matrix33 operator*(const Matrix33& m1, const Matrix33& m2)
{
    auto m3 = m1;
    m3 *= m2;
    return m3;
}

Matrix33& Matrix33::operator*=(const float& f1)
{
    Matrix33 newMat = Matrix33();
    for (int i = 0; i < 9; i++)
        m_values[i] *= f1;
    return (*this);
}

Matrix33 operator*(const Matrix33& m1, const float& f1)
{
    Matrix33 m2 = m1;
    m2 *= f1;
    return m2;
}

Vector3D operator*(const Matrix33& m1, const Vector3D& v1)
{
    Vector3D newVec = Vector3D();
    auto vecValues = v1.getValues();
    for (int i = 0; i < 3; i++) {
        float val = 0;
        for (int j = 0; j < 3; j++)
            val += vecValues[j] * m1.m_values[j + i * 3];
        if (i == 0) newVec.setX(val);
        else if (i == 1) newVec.setY(val);
        else if (i == 2) newVec.setZ(val);
    }
    return newVec;
}

#pragma endregion

#pragma region Methods

Matrix33 Matrix33::Inverse() const
{
    //On calcule le determinant
    float det = Determinant(*this);
    if (det == 0) return Matrix33(*this);   //Si le determinant est nul, alors la matrice n'aura pas d'inverse
    Matrix33 newMat = Matrix33();

    newMat.m_values[0] = m_values[4]* m_values[8] - m_values[5]* m_values[7];
    newMat.m_values[1] = m_values[2]* m_values[7] - m_values[1]* m_values[8];
    newMat.m_values[2] = m_values[1]* m_values[5] - m_values[2]* m_values[4];

    newMat.m_values[3] = m_values[5]* m_values[6] - m_values[3]* m_values[8];
    newMat.m_values[4] = m_values[0]* m_values[8] - m_values[2]* m_values[6];
    newMat.m_values[5] = m_values[2]* m_values[3] - m_values[0]* m_values[5];
    
    newMat.m_values[6] = m_values[3]* m_values[7] - m_values[4]* m_values[6];
    newMat.m_values[7] = m_values[1]* m_values[6] - m_values[0]* m_values[7];
    newMat.m_values[8] = m_values[0]* m_values[4] - m_values[1]* m_values[3];
    newMat *= 1/det;
    return newMat;
}

Matrix33 Matrix33::Transpose()
{
    Matrix33 newMat = Matrix33();
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
        newMat.m_values[i + 3*j] = m_values[j + 3*i];
    return newMat;
}

void Matrix33::rotate(const Quaternion& rotation)
{
    SetRotation(getRotation() * rotation);
}

Quaternion Matrix33::getRotation() const
{
    float w = sqrt(1 + getValueAt(0, 0) + getValueAt(1, 1) + getValueAt(2, 2)) / 2;
    float x = (getValueAt(2, 1) - getValueAt(1, 2)) / (4 * w);
    float y = (getValueAt(0, 2) - getValueAt(2, 0)) / (4 * w);
    float z = (getValueAt(1, 0) - getValueAt(0, 1)) / (4 * w);
    return Quaternion(w, x, y, z);
}

void Matrix33::SetRotation(const Quaternion& q)
{
    float x2 = q.getI() * q.getI();
    float y2 = q.getJ() * q.getJ();
    float z2 = q.getK() * q.getK();
    float xy = q.getI() * q.getJ();
    float zw = q.getK() * q.getW();
    float xz = q.getI() * q.getK();
    float yw = q.getJ() * q.getW();
    float yz = q.getJ() * q.getK();
    float xw = q.getI() * q.getW();
    m_values[0] = 1 - (2 * y2 + 2 * z2);
    m_values[1] = 2 * xy + 2 * zw;
    m_values[2] = 2 * xz - 2 * yw;
    m_values[3] = 2 * xy - 2 * zw;
    m_values[4] = 1 - (2 * x2 + 2 * z2);
    m_values[5] = 2 * yz + 2 * xw;
    m_values[6] = 2 * xz + 2 * yw;
    m_values[7] = 2 * yz - 2 * xw;
    m_values[8] = 1 - (2 * x2 + 2 * y2);
}

float Matrix33::Determinant(const Matrix33& mat)
{
    return mat.m_values[0] * mat.m_values[4] * mat.m_values[8] +
        mat.m_values[3] * mat.m_values[7] * mat.m_values[2] +
        mat.m_values[6] * mat.m_values[1] * mat.m_values[5] -
        mat.m_values[0] * mat.m_values[7] * mat.m_values[5] -
        mat.m_values[6] * mat.m_values[4] * mat.m_values[2] -
        mat.m_values[3] * mat.m_values[1] * mat.m_values[8];
}

#pragma endregion