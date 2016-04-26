#pragma once


#include "GameObject.h"

class Sphere : public GameObject
{
public:
	Sphere() {};
	~Sphere() {};

	void Init(std::string filename);
	void Init(Colour_RGBA colour);
	void Update(float speed, float dt);
	void Render();

private:

};
