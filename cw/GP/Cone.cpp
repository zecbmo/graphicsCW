#include "Cone.h"

void Cone::Init(float height, float resolution, std::string filename)
{
	scale_ = Vector3(1, 1, 1);
	texture_ = LoadTexture(filename);
	material_.Init(DEFAULT, BLUE);
	shape_.CreateCone(height, resolution);
}

void Cone::Update()
{
}

void Cone::Render()
{
	BeginObjectDrawing();
	glBindTexture(GL_TEXTURE_2D, texture_);
	material_.BindMaterial();
	shape_.Draw();
	EndObjectDrawing();
}
