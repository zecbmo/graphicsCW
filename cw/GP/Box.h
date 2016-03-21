#pragma once

#include "GameObject.h"

class Box : public GameObject
{
public:
	Box() {};
	~Box() {};

	void Init(std::string filename);
	void Update(float speed, float dt);
	void Render();

private:

};
