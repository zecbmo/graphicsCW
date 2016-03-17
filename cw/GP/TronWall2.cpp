#include "TronWall2.h"


void TronWall2::Init(float depth)
{
	position_ = Vector3(0, 0, 0);
	rotation_ = Vector3(0, 0, 0);
	scale_ = Vector3(1, 1, 1);

	texture_ = LoadTexture("Textures/tronsquare.png");
	material_.Init(DEFAULT, BLUE);

	block_one_.CreateCustomQuad(Vector3(-1, 0, 0), Vector3(-1, 10, 0), Vector3(1, 7, 0), Vector3(1, 0, 0), depth-2);

	block_two_.CreateCustomQuad(Vector3(-1, 11, 0), Vector3(-1, 20, 0), Vector3(1, 20, 0), Vector3(1, 8, 0), depth*2);

	block_three_.CreateCustomQuad(Vector3(-1, 0, -depth-2), Vector3(-1, 10, -depth - 2), Vector3(1, 7, -depth - 2), Vector3(1, 0, -depth - 2), depth-2);



}

void TronWall2::Update()
{
}

void TronWall2::Render()
{
	BeginObjectDrawing();

	material_.SetColourByTemplate(BLUE);
	material_.BindMaterial();
	glBindTexture(GL_TEXTURE_2D, texture_);
	block_one_.Draw();
	block_two_.Draw();

	//material_.SetColourByTemplate(RED);
	material_.BindMaterial();
	block_three_.Draw();

	EndObjectDrawing();
}
