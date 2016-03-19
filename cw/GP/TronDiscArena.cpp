#include "TronDiscArena.h"

void TronDiscArena::Init(Vector3 position)
{
	position_ = position;
	rotation_ = Vector3(0, 0, 0);
	scale_ = Vector3(20, 20, 20);

	floor_texture_ = LoadTexture("Textures/lightDisc.png");
	alpha_mat_.Init(DEFAULT, Colour_RGBA(1,1,1,1));
	floor_.CreateShape(DISC);
	
}

void TronDiscArena::Update()
{
}

void TronDiscArena::Render()
{
	BeginObjectDrawing();

	
	alpha_mat_.BindMaterial();
	glBindTexture(GL_TEXTURE_2D, floor_texture_);
	




	glPushMatrix();
	
	glRotatef(90, 0, 1, 0);
	glRotatef(90, 1, 0, 0);
	

	glDisable(GL_LIGHTING);
	glEnable(GL_BLEND);
	floor_.Draw();
	glDisable(GL_BLEND);
	glPopMatrix();
	glEnable(GL_LIGHTING);




	EndObjectDrawing();

}
