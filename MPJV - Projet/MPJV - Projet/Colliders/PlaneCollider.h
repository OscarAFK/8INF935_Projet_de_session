#pragma once
#include <glm/glm.hpp>
#include "Collider.h"

class PlaneCollider : public Collider
{
private:
	Vector3D m_normal;
	float m_planeOffset;

public:

	PlaneCollider(Entity* owner) : Collider(owner) { m_name = "Plane Collider"; };
	void Initialize(Vector3D normal = Vector3D(0, 1, 0), Matrix34 *offset = new Matrix34());

	Vector3D getNormal() const;
	float getPlaneOffset() const;
	void setNormal(Vector3D normal);

	colliderShapes getShape() const;

	void renderComponentUI();
};