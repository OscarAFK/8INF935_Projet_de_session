#pragma once
#include <glm/glm.hpp>
#include "Collider.h"

class PlaneCollider : public Collider
{
private:
	Vector3D m_normal;

public:

	PlaneCollider(Entity* owner) : Collider(owner) { m_name = "Plane Collider"; };
	void Initialize(Vector3D normal = Vector3D(0, 1, 0), Vector3D offset = Vector3D(0, 0, 0));

	Vector3D getNormal();
	void setNormal(Vector3D normal);

	colliderShapes getShape();

	void renderComponentUI();
};