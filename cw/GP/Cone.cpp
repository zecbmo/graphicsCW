#include "Cone.h"

void Cone::Init(float height, float resolution, std::string filename)
{
	scale_ = Vector3(1, 1, 1);
	texture_ = LoadTexture(filename);
	material_.Init(DEFAULT, BLUE);
	shape_.CreateCone(height, resolution);
}

void Cone::Update(float speed, float dt)
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

void Cone::Render()
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
