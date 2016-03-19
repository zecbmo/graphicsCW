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
	case CUBE_SIX:
		error::StringError(filename, ": Please use seperate init function for creating 6 sided skybox");
		break;
	default:
		break;
	}
}
void SkyBox::InitCubeBox(std::string ft, std::string lf, std::string rt, std::string bk, std::string up_t, std::string dn)
{
	type_ = CUBE_SIX;

	ft_ = SOIL_load_OGL_texture
		(
			ft.c_str(),
			SOIL_LOAD_AUTO,
			SOIL_CREATE_NEW_ID,
			SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB |
			SOIL_FLAG_COMPRESS_TO_DXT

			);
	if (SOIL_last_result() == "Unable to open file")
	{
		error::StringError(ft, ": Texture not set for SkyBox. Check filename.");
	}

	lf_ = SOIL_load_OGL_texture
		(
			lf.c_str(),
			SOIL_LOAD_AUTO,
			SOIL_CREATE_NEW_ID,
			SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB |
			SOIL_FLAG_COMPRESS_TO_DXT

			);
	if (SOIL_last_result() == "Unable to open file")
	{
		error::StringError(lf, ": Texture not set for SkyBox. Check filename.");
	}

	rt_ = SOIL_load_OGL_texture
		(
			rt.c_str(),
			SOIL_LOAD_AUTO,
			SOIL_CREATE_NEW_ID,
			SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB |
			SOIL_FLAG_COMPRESS_TO_DXT

			);
	if (SOIL_last_result() == "Unable to open file")
	{
		error::StringError(rt, ": Texture not set for SkyBox. Check filename.");
	}

	dn_ = SOIL_load_OGL_texture
		(
			dn.c_str(),
			SOIL_LOAD_AUTO,
			SOIL_CREATE_NEW_ID,
			SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB |
			SOIL_FLAG_COMPRESS_TO_DXT

			);
	if (SOIL_last_result() == "Unable to open file")
	{
		error::StringError(dn, ": Texture not set for SkyBox. Check filename.");
	}

	up_t_ = SOIL_load_OGL_texture
		(
			up_t.c_str(),
			SOIL_LOAD_AUTO,
			SOIL_CREATE_NEW_ID,
			SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB |
			SOIL_FLAG_COMPRESS_TO_DXT

			);
	if (SOIL_last_result() == "Unable to open file")
	{
		error::StringError(up_t, ": Texture not set for SkyBox. Check filename.");
	}

	bk_ = SOIL_load_OGL_texture
		(
			bk.c_str(),
			SOIL_LOAD_AUTO,
			SOIL_CREATE_NEW_ID,
			SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB |
			SOIL_FLAG_COMPRESS_TO_DXT

			);
	if (SOIL_last_result() == "Unable to open file")
	{
		error::StringError(bk, ": Texture not set for SkyBox. Check filename.");
	}

	front_.CreateShape(PLANE);
	back_.CreateShape(PLANE);
	left_.CreateShape(PLANE);
	right_.CreateShape(PLANE);
	up_.CreateShape(PLANE);
	down_.CreateShape(PLANE);
	face_.CreateShape(PLANE);



}
void SkyBox::Render(Vector3 camera_position, float speed)
{
	glColor4f(1, 1, 1, 1); //resets to default incase over writen by materials 
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);
	glPushMatrix();
		glTranslatef(camera_position.GetX(), camera_position.GetY(), camera_position.GetZ());
		
		
		
		Draw(speed);
		
		
		
	glPopMatrix();
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	
}
void SkyBox::Draw(float speed)
{
	glEnable(GL_TEXTURE_2D);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glScalef(4, 4, 4);


	

	if (type_ != CUBE_SIX)
	{
		
		glBindTexture(GL_TEXTURE_2D, texture_);	
		
		shape_.Draw();
		glBindTexture(GL_TEXTURE_2D, NULL);
	}
	else
	{
		
		glBindTexture(GL_TEXTURE_2D, ft_);
		glPushMatrix();
		glTranslatef(0, 0, 0.4999999);

	
		glMatrixMode(GL_TEXTURE);
		glPushMatrix(); /////////////////////////////////////////////////problem?
		glTranslatef(speed, speed, 0);
		face_.Draw();
		glPopMatrix();
		glMatrixMode(GL_MODELVIEW);
	
	



		glPopMatrix();		

		glBindTexture(GL_TEXTURE_2D, bk_);
		glPushMatrix();
		glTranslatef(0, 0, -0.4999999);
		glRotatef(180, 0, 1, 0);
		face_.Draw();
		glPopMatrix();

		glBindTexture(GL_TEXTURE_2D, lf_);
		glPushMatrix();
		glTranslatef(-0.4999999, 0, 0);
		glRotatef(-90, 0, 1, 0);
		face_.Draw();
		glPopMatrix();

		glBindTexture(GL_TEXTURE_2D, rt_);
		glPushMatrix();
		glTranslatef(0.4999999, 0, 0);
		glRotatef(90, 0, 1, 0);
		face_.Draw();
		glPopMatrix();

		glBindTexture(GL_TEXTURE_2D, up_t_);
		glPushMatrix();
		glTranslatef(0, 0.4999999, 0);
		glRotatef(-90, 1, 0, 0);
		face_.Draw();
		glPopMatrix();

		glBindTexture(GL_TEXTURE_2D, dn_);
		glPushMatrix();
		glTranslatef(0, -0.4999999, 0);
		glRotatef(90, 1, 0, 0);
		face_.Draw();
		glPopMatrix();
		
		glBindTexture(GL_TEXTURE_2D, NULL);
	}

	

}

