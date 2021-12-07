#include "Octree.h"

OctreeObject::OctreeObject(Entity* entity)
{
	m_center = entity->getComponent<Transform>()->getPosition();
	m_radius = entity->getComponent<SphereCollider>()->getRadius();
	m_entity = entity;
}

OctreeNode* OctreeNode::BuildOctree(Vector3D center, float halfWidth, int maxDepth)
{
	if (maxDepth < 0) return nullptr;
	else {
		Vector3D offset;
		float step = m_halfWidth * .5f;

		for (int i = 0; i < 8; i++) {
			//Les opération de type ( i & a ) sont des comparaison de bit. On va appliquer un mask "a" à "i", et si le résultat
			//est différent de 0 alors on retourne 1, sinon on retourne 0.
			//Ex: (3 & 2) --> 0011 & 0010 = 0010 = true
			//Ex: (5 & 4) --> 0101 & 0100 = 0100 = true
			//Ex: (2 & 4) --> 0010 & 0100 = 0000 = false
			offset.setX((i & 1) ? step : -step);	
			offset.setY((i & 2) ? step : -step);
			offset.setZ((i & 4) ? step : -step);
			m_childrens[i] = BuildOctree(m_center + offset, step, maxDepth - 1);
		}
	}
	return this;
}

int OctreeNode::getChildIndex(const Vector3D& objectPos)
{
	int index = 0;
	if (objectPos.getX() > m_center.getX()) index += 1;
	if (objectPos.getY() > m_center.getY()) index += 2;
	if (objectPos.getZ() > m_center.getZ()) index += 4;
	return index;
}

void OctreeNode::InsertObject(OctreeObject* obj)
{
	int index = 0;
	int straddle = 0; //Chevauchement

	for (int i = 0; i < 3; i++) {
		float delta = obj->m_center.getValues()[i] - m_center.getValues()[i];
		if (abs(delta) < m_halfWidth + obj->m_radius) {		//Si l'objet est en majorité dans une autre celulle, alors on ne l'ajoute pas
			straddle = 1;
			break;
		}
		//Il y a ici deux opération binaires: un "OU" et un décalage de bit vers la gauche. Ici, le décalage reviens à
		//mettre 2 à la puissance i.
		//La ligne suivante selectionne la cellule la plus appropriée, en regardant l'éloignement de l'objet par rapport au centre de la cellule.
		if (delta > 0.0f) index |= (1 << i);
	}
	if (!straddle && m_childrens[index]) {
		//Entièrement contenu dans un noeud enfant existant; on l'ajoute dans ce sous-arbre
		m_childrens[index]->InsertObject(obj);
	}
	else {
		//Il y a du chevauchement, ou aucun noeud enfant dans lequel aller, alors on connecte l'objet dans la liste connectée
		//de ce noeud
		obj->m_nextObject = m_objectList;
		m_objectList = obj;
	}
}

void OctreeNode::TestAllCollisions()
{
	const int MAX_DEPTH = 40;
	static OctreeNode* ancestorStack[MAX_DEPTH];
	static int depth = 0;

	ancestorStack[depth++] = this;
	for (int n = 0; n < depth; n++) {
		OctreeObject* a, * b;
		for (a = ancestorStack[n]->m_objectList; a; a->m_nextObject) {
			for (b = m_objectList; b; b->m_nextObject) {
				if (a == b) break;
				//TestCollision(a, b);			//Fonction à implémenter lors de la narrow phase, qui retournera une collision. On pourra alors rajouter cette collision à une liste, et la retournée à la sortie de cette fonction.
			}
		}
	}
	for (int i = 0; i < 8; i++) {
		if (m_childrens[i]) m_childrens[i]->TestAllCollisions();
	}
	depth--;
}


