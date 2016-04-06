#pragma once
#include <string>
#include <iostream>

class Task
{
public:
	Task() {};
	virtual ~Task() {};
	virtual void Run() = 0;
};

