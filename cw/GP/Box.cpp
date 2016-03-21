#include "Box.h"

void Box::Init(std::string filename)
{
	scale_ = Vector3(1, 1, 1);
	texture_ = LoadTexture(filename);
	material_.Init(DEFAULT, WHITE);
	shape_.CreateShape(CUBE_ST);
}

void Box::Update(float speed, float dt)
{
}

void Box::Render()
{
	BeginObjectDrawing();
	glBindTexture(GL_TEXTURE_2D, texture_);
	material_.BindMaterial();
	shape_.Draw();
	EndObjectDrawing();
}
