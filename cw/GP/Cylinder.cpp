#include "Cylinder.h"

void Cylinder::Init(float resolution, float height, std::string filename)
{
	scale_ = Vector3(1, 1, 1);
	texture_ = LoadTexture(filename);
	material_.Init(DEFAULT, WHITE);
	shape_.CreateCylinder(resolution, height);
}

void Cylinder::Update(float speed, float dt)
{
	if (moving_)
	{
		speed_ += speed*dt;
	}
	else
	{
		speed_ = 0;
	}
}

void Cylinder::Render()
{
	BeginObjectDrawing();
	glBindTexture(GL_TEXTURE_2D, texture_);
	material_.BindMaterial();


	glMatrixMode(GL_TEXTURE);
	glPushMatrix(); /////////////////////////////////////////////////problem?
	glTranslatef(0, speed_, 0);
	shape_.Draw();
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);



	EndObjectDrawing();
}
