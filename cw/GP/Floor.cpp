#include "Floor.h"

void Floor::Init(float size, float number_of_textures, std::string filename)
{
	position_ = Vector3(0, 0, 0);
	rotation_ = Vector3(90, 0, 0);
	scale_ = Vector3(size, size, size);

	texture_ = LoadTexture(filename);
	material_.Init(DEFAULT, WHITE);
	shape_.CreateShape(PLANE_TILED, number_of_textures);


}

void Floor::Render()
{

	glPushMatrix();

	//do the transformations of the game object first
	glTranslatef(position_.GetX(), position_.GetY(), position_.GetZ());
	glRotatef(rotation_.GetX(), 1, 0, 0);
	glRotatef(rotation_.GetY(), 0, 1, 0);
	glRotatef(rotation_.GetZ(), 0, 0, 1);
	glScalef(scale_.GetX(), scale_.GetY(), scale_.GetZ());


	material_.BindMaterial();
	glBindTexture(GL_TEXTURE_2D, texture_);
	shape_.Draw();


	glPopMatrix();

}
