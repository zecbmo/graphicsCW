#include "TronDiscArena.h"

void TronDiscArena::Init(Vector3 position)
{
	position_ = position;
	rotation_ = Vector3(0, 0, 0);
	scale_ = Vector3(20, 20, 20);

	floor_texture_ = LoadTexture("Textures/discouter.png");
	alpha_mat_.Init(DEFAULT, Colour_RGBA(1,1,1,1));
	floor_.CreateShape(DISC);

	floor_inner_texture_ = LoadTexture("Textures/discinner.png");
	floor_inner_.CreateShape(DISC);
	rot_speed_ = 5;
}

void TronDiscArena::Update(float dt)
{
	rot_speed_ += 8 * dt;

}

void TronDiscArena::Render()
{
	BeginObjectDrawing();

	
	alpha_mat_.BindMaterial();
	glBindTexture(GL_TEXTURE_2D, floor_texture_);
	




	glPushMatrix();
	
	glRotatef(0, 0, 1, 0);
	glRotatef(90, 1, 0, 0);
	

	glDisable(GL_LIGHTING);
	glEnable(GL_BLEND);

	floor_.Draw();

	glPushMatrix();
	glTranslatef(0,0, -0.002);
	glRotatef(rot_speed_, 0, 0, 1);
	glBindTexture(GL_TEXTURE_2D, floor_inner_texture_);
	floor_inner_.Draw();
	glPopMatrix();

	glDisable(GL_BLEND);
	glPopMatrix();
	glEnable(GL_LIGHTING);




	EndObjectDrawing();

}
