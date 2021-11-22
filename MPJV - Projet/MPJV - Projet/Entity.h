#pragma once
#include <vector>
#include <string>
#include "Component.h"

class Entity
{
public:
	std::string m_name = "test";
	Entity() = default;
	Entity(std::vector<Component*> components) {
		m_components = components;
	}
	~Entity() = default;
	std::vector<Component*> m_components;


	template <typename T = Component>
	T* getComponent()
	{
		for (size_t i = 0; i < m_components.size(); i++)
		{
			if (dynamic_cast<T*>(m_components[i]))
			{
				return (T*)m_components[i];
			}
		}
		return nullptr;
	}

	template <typename T = Component>
	void addComponent()
	{
		m_components.push_back(new T(this));
	}

private:
	
};
