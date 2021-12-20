#pragma once
#include "../Vector3D.h"
#include "../Entity.h"
#include "SphereCollider.h"
#include "CollisionDetector.h"

struct OctreeObject {
	OctreeObject(Entity * entity);
	Vector3D m_center;
	float m_radius;
	Entity* m_entity;
	OctreeObject* m_nextObject = nullptr;
};

struct OctreeNode {
	Vector3D m_center;
	float m_halfWidth;
	OctreeNode* m_childrens[8];		//On aurrait pu faire un "Linear Octree", mais je pr�f�re d�j� tester celui-ci.
	OctreeObject* m_objectList;

	OctreeNode();

	int	getChildIndex(const Vector3D& objectPos);	
	void InsertObject(OctreeObject * obj);
	void TestAllCollisions(CollisionData *collisionData);
	void TestCollision(OctreeObject *a, OctreeObject *b, CollisionData* collisionData);
	static OctreeNode* BuildOctree(Vector3D center, float halfWidth, int maxDepth);
};