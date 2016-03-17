#include "TronWall.h"

void TronWall::Init(float depth)
{
	position_ = Vector3(0, 0, 0);
	rotation_ = Vector3(0, 0, 0);
	scale_ = Vector3(1, 1, 1);

	texture_ = LoadTexture("Textures/tronsquare.png");
	material_.Init(DEFAULT, BLUE);
	
	block_one_.CreateCustomQuad(Vector3(-1,0,0), Vector3(-1,10,0), Vector3(1,7,0), Vector3(1,0,0), depth );
	
	block_two_.CreateCustomQuad(Vector3(-1, 11, 0), Vector3(-1, 20, 0), Vector3(1, 20, 0), Vector3(1, 8, 0), depth);

	block_three_.CreateCustomQuad(Vector3(-0.9, 0, -0.5), Vector3(-0.9, 2, -0.5), Vector3(1.01, 2, -0.5), Vector3(1.01, 0, -0.5), depth-1);

	

}

void TronWall::Update()
{
}

void TronWall::Render()
{
	BeginObjectDrawing();

	material_.SetColourByTemplate(BLUE);
	material_.BindMaterial();
	glBindTexture(GL_TEXTURE_2D, texture_);
	block_one_.Draw();
	block_two_.Draw();

	material_.SetColour(Colour_RGBA(0, 0.5, 1, 1));
	material_.BindMaterial();
	block_three_.Draw();

	EndObjectDrawing();

	
}
