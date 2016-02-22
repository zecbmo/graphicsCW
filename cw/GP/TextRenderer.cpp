#include "TextRenderer.h"
#define GRID_WIDTH 16
#define GRID_HIGHT 16


BitmapTextRenderer::BitmapTextRenderer()
{
}


BitmapTextRenderer::~BitmapTextRenderer()
{
}
void BitmapTextRenderer::init(std::string filename)
{
	glEnable(GL_TEXTURE_2D);

	fontTexture = SOIL_load_OGL_texture
		(
			filename.c_str(),
			SOIL_LOAD_AUTO,
			SOIL_CREATE_NEW_ID,
			SOIL_FLAG_NTSC_SAFE_RGB

			);

	std::string temp = SOIL_last_result();
	if (fontTexture == NULL)
	{
		char buffer[255];
		sprintf_s(buffer, "NO PHOTO LOADED");
		//std::cout << "fps: " << framecounter << std::endl;
		OutputDebugString(buffer);
	}

}

void BitmapTextRenderer::drawText(std::string text, float x, float y, float charWidth, float charHeight)
{
	glTranslatef(x, y, 0);
	for (int i = 0; i < text.length(); i++)
	{
		//get ascii value
		int asciiCode = text[i];

		//set the cell size (16 within texture)
		float cellsize = 1.0f / GRID_WIDTH;

		//x coord is greatest int smaller than the remainder of ascii value / amount of cells on the x axis
		float cellX = ((int)asciiCode % GRID_WIDTH)*cellsize;
		//and similar for y except divided 
		float cellY = ((int)asciiCode / GRID_WIDTH)*cellsize;

		
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, fontTexture);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glBegin(GL_QUADS);	//Begin drawing state

		float z = 0.07;
		 
		      
		

		glTexCoord2f(cellX, cellY + cellsize);
		glVertex3f(i * charWidth / 3, y, z);
		glTexCoord2f(cellX + cellsize, cellY + cellsize);
		glVertex3f(i * charWidth / 3 + charWidth / 2, y, z);
		glTexCoord2f(cellX + cellsize, cellY);
		glVertex3f(i * charWidth / 3 + charWidth / 2, y + charHeight, z);
		glTexCoord2f(cellX, cellY);
		glVertex3f(i * charWidth / 3, y + charHeight, z);

		glEnd();
	

	
	}

	glBindTexture(GL_TEXTURE_2D, NULL);

}