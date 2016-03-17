#include "TronLight.h"

void TronLight::Init(Vector3 position)
{
	position_ = position;
	scale_ = Vector3(5,3,5);

	block_.CreateShape(CUBE_ST);
	block_texture_ = LoadTexture("Textures/tronsquare.png");
	material_.Init(DEFAULT, PURPLE);

}

void TronLight::Update()
{
}

void TronLight::Render()
{
	BeginObjectDrawing();

	glPushMatrix();

	//material_.SetColour(Colour_RGBA(0, 0.5, 1, 1));
	material_.BindMaterial();
	glBindTexture(GL_TEXTURE_2D, block_texture_);
	block_.Draw();

	glPopMatrix();

	EndObjectDrawing();
}
