#pragma once
#include <glm/glm.hpp>
#include "../Entity.h"

enum colliderShapes { SPHERE };

class Collider : public Component
{
private:
	Vector3D m_offset;

public:

	Collider(Entity* owner) : Component(owner) {};;
	
	Vector3D getOffset();
	void setOffset(Vector3D offset);

	virtual colliderShapes getShape() = 0;
};
