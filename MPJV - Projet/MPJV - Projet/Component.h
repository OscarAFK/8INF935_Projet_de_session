#pragma once
#include <string>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

class Entity;

class Component
{
public:
	Component(Entity* owner)
	{
		m_owner = owner;
	}
	virtual ~Component() = default;

	virtual void renderComponentUI() = 0;

	std::string getName()
	{
		return m_name;
	}

protected:
	std::string m_name;
	Entity* m_owner;
};
