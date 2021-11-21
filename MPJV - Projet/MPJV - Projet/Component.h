#pragma once

class Entity {};

class Component
{
public:
	Component();
	~Component();
	Entity owner;

private:

};

Component::Component()
{
}

Component::~Component()
{
}