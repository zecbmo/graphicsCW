#pragma once
#include "GameObject.h"

class NewFloor : public GameObject
{
public:
	NewFloor() {};
	~NewFloor() {};

	void Init(float size, std::string filename);
	void Render();

private:

};

