#pragma once
#include "GameObject.h"

class TronDiscArena : public GameObject
{
public:
	TronDiscArena() {};
	~TronDiscArena() {};

	void Init(Vector3 position);
	void Update(float dt);
	void Render();

private:

	Shapes floor_;
	Material alpha_mat_;
	GLuint floor_texture_;
	Shapes floor_inner_;
	GLuint floor_inner_texture_;
	float rot_speed_;

};

