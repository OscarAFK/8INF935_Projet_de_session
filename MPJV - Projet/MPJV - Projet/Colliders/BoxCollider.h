#pragma once
#include <glm/glm.hpp>
#include "Collider.h"

class BoxCollider : public Collider
{
private:
	Vector3D m_halfSize;

public:

	BoxCollider(Entity* owner) : Collider(owner) { m_name = "Box Collider"; };
	void Initialize(Vector3D halfSize = Vector3D(0.5f, 0.5f, 0.5f), Vector3D offset = Vector3D(0, 0, 0));

	Vector3D getHalfSize();
	void setHalfSize(Vector3D halfSize);

	colliderShapes getShape();

	void renderComponentUI();
};