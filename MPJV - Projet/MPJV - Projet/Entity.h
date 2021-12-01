#pragma once
#include <vector>
#include <string>
#include "Transform.h"
#include "UniqueID.h"


class Entity : public UniqueID
{
public:
	Transform* transform;

	Entity(std::string name) {
		m_name = name;
		transform = addComponent<Transform>();
	}
	~Entity() = default;

	std::string getName()
	{
		return m_name;
	}

	std::vector<Component*> getComponents()
	{
		return m_components;
	}

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
	std::vector<T*> getComponents()
	{
		std::vector<T*> components;
		for (size_t i = 0; i < m_components.size(); i++)
		{
			if (dynamic_cast<T*>(m_components[i]))
			{
				components.push_back(m_components[i]);
			}
		}
		return components;
	}

	template <typename T = Component>
	T* addComponent()
	{
		T* newComponent = new T(this);
		m_components.push_back(newComponent);
		return newComponent;
	}

private:
	std::string m_name = "Entity";
	std::vector<Component*> m_components;
};
