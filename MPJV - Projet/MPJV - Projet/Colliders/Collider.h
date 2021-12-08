#pragma once
#include <glm/glm.hpp>
#include "../Entity.h"
#include "../Utilitaire/Rigidbody.h"

enum colliderShapes { SPHERE, PLANE, BOX };

class Collider : public Component
{
private:
	Vector3D m_offset;
	Rigidbody* rigidbody;

public:

	Collider(Entity* owner) : Component(owner) {};;
	
	Vector3D getOffset();
	void setOffset(Vector3D offset);

	virtual colliderShapes getShape() = 0;
};
