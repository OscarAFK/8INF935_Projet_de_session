#pragma once
#include <glm/glm.hpp>
#include "Collider.h"

class SphereCollider : public Collider
{
private:
	float m_radius;

public:

	SphereCollider(Entity* owner) : Collider(owner) { m_name = "Sphere Collider"; };
	void Initialize(float radius = 1, Vector3D offset = Vector3D(0,0,0));
	
	float getRadius();
	float setRadius();

	colliderShapes getShape();

	void renderComponentUI();
};
