#include "Collider.h"

Vector3D Collider::getOffset()
{
    return m_offset;
}

void Collider::setOffset(Vector3D offset)
{
    m_offset = offset;
}
