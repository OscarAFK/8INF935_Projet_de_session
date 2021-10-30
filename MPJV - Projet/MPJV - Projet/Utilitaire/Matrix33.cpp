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
float Matrix33::getValueAt(int i, int j)
{
    return m_values[i + j*3];
}

#pragma endregion

#pragma region Operators

Matrix33 Matrix33::operator*(const Matrix33& other) const
{
    Matrix33 newMat = Matrix33();
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            for(int k = 0; k < 3; k++)
                newMat.m_values[i + j * 3] = m_values[i + k*3] * other.m_values[k + j*3];
    return newMat;
}

Matrix33 Matrix33::operator*(const float& other) const
{
    Matrix33 newMat = Matrix33();
    for (int i = 0; i < 9; i++)
        newMat.m_values[i] = m_values[i] * other;
    return newMat;
}

Matrix33 Matrix33::operator*(const Vector3D& other) const
{
    return Matrix33();
}

#pragma endregion

#pragma region Methods

Matrix33 Matrix33::Inverse()
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

void Matrix33::SetOrientation(const Quaternion& q)
{

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
