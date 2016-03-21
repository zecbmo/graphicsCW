#include "Cylinder.h"

void Cylinder::Init(float resolution, std::string filename)
{
	scale_ = Vector3(1, 1, 1);
	texture_ = LoadTexture(filename);
	material_.Init(DEFAULT, WHITE);
	shape_.CreateShape(CYLINDER, resolution);
}

void Cylinder::Update(float speed, float dt)
{
	float z = rotation_.GetZ();
	rotation_.SetZ(z+(speed*dt));
}

void Cylinder::Render()
{
	BeginObjectDrawing();
	glBindTexture(GL_TEXTURE_2D, texture_);
	material_.BindMaterial();
	shape_.Draw();
	EndObjectDrawing();
}
