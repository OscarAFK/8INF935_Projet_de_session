#include "Bvh.h"

BvhNode::BvhNode()
{
	childrens = std::vector<BvhNode>();
}

Rigidbody* BvhNode::getRigidbody()
{
	return rigidbody;
}

std::vector<BvhNode> BvhNode::getChildrens()
{
	return childrens;
}

bool BvhNode::hasRigidbody()
{
	if (rigidbody != nullptr)
		return true;
	else return false;
}

void BvhNode::setRigidbody(Rigidbody* _rigidbody)
{
	rigidbody = _rigidbody;
}

void BvhNode::setChildrens(std::vector<BvhNode> _childrens)
{
	childrens = _childrens;
}

BvhNode Bvh::getStart()
{
	return start;
}

void Bvh::addStart(BvhNode node)
{
	start = node;
}
