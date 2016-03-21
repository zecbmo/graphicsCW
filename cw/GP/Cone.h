#pragma once

#include "GameObject.h"

class Cone : public GameObject
{
public:
	Cone() {};
	~Cone() {};

	void Init(float height, float resolution, std::string filename );
	void Update();
	void Render();

private:

};

