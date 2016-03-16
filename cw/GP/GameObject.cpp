#include "GameObject.h"

void GameObject::Init()
{
	//samples
	//create materials and shapes
	//load in textures

	//scale = 1 1 1 - dont forget or then no game object

}

void GameObject::Update()
{
	//update position etc
}

void GameObject::Render()
{
	glPushMatrix();

	//do the transformations of the game object first
	glTranslatef(position_.GetX(), position_.GetY(), position_.GetZ());
	glRotatef(rotation_.GetX(), 1, 0, 0);
	glRotatef(rotation_.GetY(), 0, 1, 0);
	glRotatef(rotation_.GetZ(), 0, 0, 1);
	glScalef(scale_.GetX(), scale_.GetY(), scale_.GetZ());

	if (scale_ == Vector3(0, 0, 0))
	{
		error::ErrorMessage("Scale set to 0,0,0 in a GameObject");
	}

	//then render and do individual transforms from here


	material_.BindMaterial();
	shape_.Draw();



	glPopMatrix();
}

GLuint GameObject::LoadTexture(std::string filename)
{
	GLuint text = SOIL_load_OGL_texture
	(
		filename.c_str(),
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB |
		SOIL_FLAG_COMPRESS_TO_DXT

	);
	if (SOIL_last_result() == "Unable to open file")
	{
		error::StringError(filename, ": Texture not set for GameObject. Check filename.");
	}

	return text;
	
}
