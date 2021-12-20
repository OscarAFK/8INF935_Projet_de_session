#pragma once
#include <glm/glm.hpp>
#include "../Entity.h"
#include "../Utilitaire/Rigidbody.h"

enum colliderShapes { SPHERE, PLANE, BOX };

class Collider : public Component
{
protected:
	//Vector3D m_offset;
	Matrix34 m_offset;
	Rigidbody* rigidbody;

public:

	Collider(Entity* owner) : Component(owner) { rigidbody = owner->getComponent<Rigidbody>(); 
												m_offset = owner->transform->getTransformMatrix(); };
	
	const Matrix34& getOffset() const;
	Rigidbody* getRigidbody() const;

	virtual colliderShapes getShape() const = 0;
};
