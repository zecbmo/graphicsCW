#pragma once
#include "GameObject.h"

class TronDiscArena : public GameObject
{
public:
	TronDiscArena() {};
	~TronDiscArena() {};

	void Init(Vector3 position);
	void Update();
	void Render();

private:

	Shapes floor_;
	Material alpha_mat_;
	GLuint floor_texture_;

};

