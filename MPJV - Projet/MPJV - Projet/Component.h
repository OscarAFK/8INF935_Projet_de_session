#pragma once

class Entity;

class Component
{
public:
	Component(Entity* owner)
	{
		m_owner = owner;
	}
	virtual ~Component() = default;

private:

	Entity* m_owner;
};
