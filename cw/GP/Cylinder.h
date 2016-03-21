#pragma once

#include "GameObject.h"

class Cylinder : public GameObject
{
public:
	Cylinder() {};
	~Cylinder() {};

	void Init(float resolution, std::string filename);
	void Update(float speed, float dt);
	void Render();

private:

};

