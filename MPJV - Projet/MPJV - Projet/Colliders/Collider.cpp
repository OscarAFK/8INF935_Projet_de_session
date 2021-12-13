#include "Collider.h"

Transform *Collider::getOffset() const
{
    return m_offset;
}

Rigidbody* Collider::getRigidbody() const
{
    return rigidbody;
}