#pragma once
#include <vector>
#include "ForceGenerator.h"

class ForceRegistry
{
private:
	struct ForceEntry
	{
		ForceEntry(Rigidbody* rg, ForceGenerator* fg) : rigidbody{ rg }, forceGenerator{ fg }{};
		Rigidbody* rigidbody;
		ForceGenerator* forceGenerator;
	};

	//using Registry = std::vector<ForceEntry>;
	std::vector<ForceEntry> m_registry;

public:
	void addEntry(ForceEntry entry);
	void addEntry(Rigidbody* rg, ForceGenerator* forceGenerator);
	void removeEntry(int index);
	void updateForce(float deltaTime);
};