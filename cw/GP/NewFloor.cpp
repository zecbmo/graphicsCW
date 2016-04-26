#include "NewFloor.h"

void NewFloor::Init(float size, std::string filename)
{
	position_ = Vector3(0, 0, 0);
	//rotation_ = Vector3(-90, 0, 0);
	scale_ = Vector3(1, 1, 1);

	texture_ = LoadTexture(filename);
	material_.Init(DEFAULT, WHITE);
	shape_.CreateShape(PLANE_BIG, size);


}

void NewFloor::Render()
{

	BeginObjectDrawing();

	material_.BindMaterial();
	glBindTexture(GL_TEXTURE_2D, texture_);
	shape_.Draw();


	EndObjectDrawing();

}