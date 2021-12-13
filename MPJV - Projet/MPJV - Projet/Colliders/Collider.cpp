#include "Collider.h"

Vector3D Collider::getOffset() const
{
    return m_offset;
}

Rigidbody* Collider::getRigidbody() const
{
    return rigidbody;
}


void Collider::setOffset(Vector3D offset)
{
    m_offset = offset;
}
