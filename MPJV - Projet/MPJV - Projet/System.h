#pragma once

class System
{
public:
	System();
	~System();
	virtual void Tick() = 0;

private:

};

System::System()
{
}

System::~System()
{
}