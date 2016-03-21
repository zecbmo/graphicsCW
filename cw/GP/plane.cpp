#include "plane.h"

void Plane::Init(float size, float number_of_textures, std::string filename)
{
	position_ = Vector3(0, 0, 0);
	rotation_ = Vector3(0, 0, 0);
	scale_ = Vector3(size, size, size);

	texture_ = LoadTexture(filename);
	material_.Init(DEFAULT, WHITE);
	shape_.CreateShape(PLANE_TILED, number_of_textures);


}

void Plane::Render()
{

	BeginObjectDrawing();

	material_.BindMaterial();
	glBindTexture(GL_TEXTURE_2D, texture_);
	shape_.Draw();


	EndObjectDrawing();

}
