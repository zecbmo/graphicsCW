#pragma once
#include "GameObject.h"

class Floor : public GameObject
{
public:
	Floor() {};
	~Floor() {};
	
	void Init(float size, float number_of_textures, std::string filename);
	void Render();

private:

};

