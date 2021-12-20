#include "Collider.h"

const Matrix34* Collider::getOffset() const
{
    return m_offset;
}

Rigidbody* Collider::getRigidbody() const
{
    return rigidbody;
}