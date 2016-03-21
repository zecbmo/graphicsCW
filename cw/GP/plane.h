#pragma once

#pragma once
#include "GameObject.h"

class Plane : public GameObject
{
public:
	Plane() {};
	~Plane() {};

	void Init(float size, float number_of_textures, std::string filename);
	void Render();

private:

};

