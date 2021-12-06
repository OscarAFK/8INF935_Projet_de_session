#pragma once
#include "Rigidbody.h"
#include <iostream>

class BvhNode {

public:
	BvhNode();
	~BvhNode() = default;

	Rigidbody* getRigidbody();
	std::vector<BvhNode> getChildrens();

	bool hasRigidbody();

	void setRigidbody(Rigidbody* _rigidbody);
	void setChildrens(std::vector<BvhNode> _childrens);

private:
	Rigidbody * rigidbody;
	std::vector<BvhNode> childrens;
};

class Bvh {
public:
	Bvh() = default;
	~Bvh() = default;

	BvhNode getStart();
	void addStart(BvhNode node);

private:
	BvhNode start;
};