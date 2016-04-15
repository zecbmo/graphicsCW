#include "LoadingScene.h"

LoadingScene::LoadingScene()
{
}

LoadingScene::~LoadingScene()
{
}
void LoadingScene::Init(HWND* wnd, Input* in, float* dt, HDC hdc, HGLRC hrc, HGLRC hrc2)
{
	InitHelper(wnd, in, dt);
	hdc_ = hdc;
	hrc_ = hrc;
	hrc2_ = hrc2;
	scene_to_load_ = LOADING_SCENE;

	//////// Lighting
	glDisable(GL_LIGHTING);
	title_ = "Loading Scene";

	/////// Textures 
	//cameras
	camera_manager_.Init(input_, dt, &screenRect, hwnd_);
	camera_manager_.CreateCamera(FIXED_POSITION, "fixed one");
	camera_manager_.ChangeCamera("fixed one");
	camera_manager_.CurrentCamera()->SetPosition(Vector3(0, 0, 10));

	loading_screen_.Init(10, 1, "Textures/loading.png");
	loading_screen_.SetScale(150, 90, 1);

	loading_bar_.Init(10, 1, "Textures/loading_bar.png");
	loading_bar_.SetScale(20, 20, 1);

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

}

void LoadingScene::Update()
{
	SharedControls();
	camera_manager_.Update();
	Vector3 temp = loading_bar_.GetRotation();
	loading_bar_.SetRotation(temp.GetX()+1,0,0);

	Render();
}
void LoadingScene::Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);// Clear The Screen And The Depth Buffer
	glLoadIdentity();// load Identity Matrix
	camera_manager_.Render();
	

	//////////////////////////////////////switch to ortho
	glDisable(GL_LIGHTING);
	glDepthMask(GL_FALSE);  // disable writes to Z-Buffer
	glDisable(GL_DEPTH_TEST);  // disable depth-testing
	glMatrixMode(GL_PROJECTION);					// Select Projection
	glPushMatrix();							// Push The Matrix
	glLoadIdentity();						// Reset The Matrix
	glOrtho(0, screenRect.right, -screenRect.bottom, 0, -10, 10);				// Select Ortho Mode, 0,0 to start fropm the top left
	glMatrixMode(GL_MODELVIEW);					// Select Modelview Matrix
	glPushMatrix();							// Push The Matrix
	glLoadIdentity();

	/////////////////////////////////////  GUI drawing goes here


	glPushMatrix();
	GUIToScreenSize(0.5, 0.5);
	loading_screen_.Render();
	glPopMatrix();

	glPushMatrix();
	GUIToScreenSize(0.5, 0.5);
	loading_bar_.Render();
	glPopMatrix();




	///////////////////////////////////////// switch to projection


	glMatrixMode(GL_PROJECTION);					// Select Projection
	glPopMatrix();							// Pop The Matrix
	glMatrixMode(GL_MODELVIEW);					// Select Modelview
	glPopMatrix();
	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);  // disable writes to Z-Buffer
	glEnable(GL_LIGHTING);



	SwapBuffers(hdc_);// Swap the frame buffers.
}
