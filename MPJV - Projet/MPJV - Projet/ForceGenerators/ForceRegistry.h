#pragma once
#include <vector>
#include "ForceGenerator.h"

class ForceRegistry
{
private:
	struct ForceEntry
	{
		ForceEntry(Rigidbody* rg, ForceGenerator* pfg) : rigidbody{ rg }, forceGenerator{ pfg }{};
		Rigidbody* rigidbody;
		ForceGenerator* forceGenerator;
	};

	using Registry = std::vector<ForceEntry>;
	Registry m_registry;

public:
	void addEntry(ForceEntry entry);
	void addEntry(Rigidbody* particle, ForceGenerator* forceGenerator);
	void removeEntry(int index);
	void updateForce(float deltaTime);
};