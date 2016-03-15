#include "SkyBox.h"

void SkyBox::Init(SkyBoxType type, std::string filename)
{
	type_ = type;

	texture_ = SOIL_load_OGL_texture
		(
			filename.c_str(),
			SOIL_LOAD_AUTO,
			SOIL_CREATE_NEW_ID,
			SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB |
			SOIL_FLAG_COMPRESS_TO_DXT

			);
	if (SOIL_last_result() == "Unable to open file")
	{
		error::StringError(filename, ": Texture not set for SkyBox. Check filename.");
	}
	switch (type_)
	{
	case CUBE_SKY:
		shape_.CreateShape(CUBE_CT);
		break;
	case SPHERE_SKY:
		shape_.CreateShape(SPHERE);
		break;
	default:
		break;
	}
}
void SkyBox::Render(Vector3 camera_position)
{
	glColor4f(1, 1, 1, 1); //resets to default incase over writen by materials 
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);
	glPushMatrix();
		glTranslatef(camera_position.GetX(), camera_position.GetY(), camera_position.GetZ());
		Draw();
	glPopMatrix();
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	
}
void SkyBox::Draw()
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture_);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glScalef(10, 10, 10);
	shape_.Draw();
	


	glBindTexture(GL_TEXTURE_2D, NULL);
	glDisable(GL_TEXTURE_2D);

}

void SkyBox::MakeCube()
{
	cube_ = glGenLists(1);
	glNewList(cube_, GL_COMPILE);



	glEndList();


}
