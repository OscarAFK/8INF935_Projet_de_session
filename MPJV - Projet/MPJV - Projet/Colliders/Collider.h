#pragma once
#include <glm/glm.hpp>
#include "../Entity.h"
#include "../Utilitaire/Rigidbody.h"

enum colliderShapes { SPHERE, PLANE, BOX };

class Collider : public Component
{
protected:
	Vector3D m_offset;
	Rigidbody* rigidbody;

public:

	Collider(Entity* owner) : Component(owner) { rigidbody = owner->getComponent<Rigidbody>(); };
	
	Vector3D getOffset() const;
	Rigidbody* getRigidbody() const;
	void setOffset(Vector3D offset);

	virtual colliderShapes getShape() const = 0;
};
