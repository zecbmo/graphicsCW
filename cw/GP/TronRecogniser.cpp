#include "TronRecogniser.h"


void TronRecogniser::Init(float depth)
{
	position_ = Vector3(0, 0, 0);
	rotation_ = Vector3(0, 0, 0);
	scale_ = Vector3(1, 1, 1);

	texture_ = LoadTexture("Textures/tronsquare.png");
	material_.Init(DEFAULT, BLUE);

	//points where created with the help of some graph paper
	//left_leg_.CreateCustomQuad(Vector3(), Vector3(), Vector3(), Vector3(), depth);
	left_leg_.CreateCustomQuad(Vector3(0,0,0), Vector3(0,6,0), Vector3(1.25,6,0), Vector3(1.25,0,0), depth);
	left_foot_.CreateCustomQuad(Vector3(1.35,0,0), Vector3(1.35,0.25,0), Vector3(1.35,1,0), Vector3(2.35,0,0), depth);

	leg_brigde_.CreateCustomQuad(Vector3(0,6.25,0), Vector3(0,6.75,0), Vector3(10,6.75,0), Vector3(10,6.25,0), depth);
	
	right_leg_.CreateCustomQuad(Vector3(8.75,0,0), Vector3(8.75,6,0), Vector3(10,6,0), Vector3(10,0,0), depth);
	right_foot_.CreateCustomQuad(Vector3(7.65,0,0), Vector3(8.65,1,0), Vector3(8.65,0.5,0), Vector3(8.65,0,0), depth);

	ballsack_.CreateCustomQuad(Vector3(4.25,5.75,0), Vector3(4.0,6,0), Vector3(6,6,0), Vector3(5.75,5.75,0), depth);

	left_sqaure_.CreateCustomQuad(Vector3(0,7,0), Vector3(0,8,0), Vector3(1.25,8,0), Vector3(1.25,7,0), depth);
	right_sqaure_.CreateCustomQuad(Vector3(8.75,7,0), Vector3(8.75,8,0), Vector3(10,8,0), Vector3(10,7,0), depth);

	left_mini_.CreateCustomQuad(Vector3(1.35,7.4,0), Vector3(1.35,7.6,0), Vector3(1.85,7.6,0), Vector3(1.85,7.4,0), depth);
	right_mini_.CreateCustomQuad(Vector3(8.15,7.4,0), Vector3(8.15,7.6,0), Vector3(8.65,7.6,0), Vector3(8.65,7.4,0), depth);

	centre_square_.CreateCustomQuad(Vector3(4.0, 7, 0), Vector3( 4.0, 7.2,0), Vector3(6,7.2,0), Vector3(6,7,0), depth);

	left_top_.CreateCustomQuad(Vector3(-0.25,8.25,0), Vector3(-0.25, 8.5,0), Vector3(4.75,8.5,0), Vector3(4.75,8.25,0), depth);
	right_top_.CreateCustomQuad(Vector3(5.25,8.25,0), Vector3(5.25,8.5,0), Vector3(10.25,8.5,0), Vector3(10.25,8.25,0), depth);

	centre_quad_.CreateCustomQuad(Vector3(3,7.3,0), Vector3(2,8,0), Vector3(8,8,0), Vector3(7,7.3,0), depth);
	top_hat_.CreateCustomQuad(Vector3(2,8.75,0), Vector3(4,9.75,0), Vector3(6,9.75,0), Vector3(8,8.75,0), depth);
}

void TronRecogniser::Update()
{
}

void TronRecogniser::Render()
{
	glDisable(GL_LIGHTING);
	BeginObjectDrawing();

	material_.SetColourByTemplate(RED);
	material_.BindMaterial();
	glBindTexture(GL_TEXTURE_2D, texture_);

	left_leg_.Draw();
	left_foot_.Draw();
	leg_brigde_.Draw();
	right_leg_.Draw();
	right_foot_.Draw();
	ballsack_.Draw();
	left_sqaure_.Draw();
	right_sqaure_.Draw();
	left_mini_.Draw();
	right_mini_.Draw();
	centre_square_.Draw();
	left_top_.Draw();
	right_top_.Draw();
	centre_quad_.Draw();
	top_hat_.Draw();
	material_.SetColour(Colour_RGBA(0, 0.5, 1, 1));
	material_.BindMaterial();
	//block_three_.Draw();



	EndObjectDrawing();
	glEnable(GL_LIGHTING);


}
