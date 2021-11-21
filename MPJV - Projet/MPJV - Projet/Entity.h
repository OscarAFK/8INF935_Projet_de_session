#pragma once
#include <vector>
#include "Component.h"

class Entity
{
public:
	Entity();
	~Entity();
	std::vector<Component> components;
	template <typename T>
	Component GetComponent()
	{
		for (size_t i = 0; i < components.size(); i++)
		{
			if (typeid(components[i]) == typeid(T))
			{
				return components[i];
			}
		}
		return NULL;
	}

private:

};

Entity::Entity()
{
}

Entity::~Entity()
{
}
