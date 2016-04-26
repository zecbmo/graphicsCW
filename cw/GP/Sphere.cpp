#include "Sphere.h"

void Sphere::Init(std::string filename)
{
	scale_ = Vector3(1, 1, 1);
	texture_ = LoadTexture(filename);
	material_.Init(DEFAULT, WHITE);
	shape_.CreateShape(SPHERE);
}
void Sphere::Init(Colour_RGBA colour)
{
	scale_ = Vector3(1, 1, 1);
	texture_ = NULL;
	material_.Init(DEFAULT, colour);
	shape_.CreateShape(SPHERE);
}
void Sphere::Update(float speed, float dt)
{
}

void Sphere::Render()
{
	BeginObjectDrawing();
	glBindTexture(GL_TEXTURE_2D, texture_);
	material_.BindMaterial();
	shape_.Draw();
	EndObjectDrawing();
}