#pragma once
#include "GameObject.h"

class TronLight : public GameObject
{
public:
	TronLight(){};
	~TronLight(){};

	void Init(Vector3 position);
	void Update();
	void Render();

private:
	Shapes block_;
	Shapes light_ray_;
	Shapes cone_;

	GLuint light_texture_;
	GLuint cone_texture_;
	GLuint block_texture_;

};

