#include "MenuScene.h"

MenuScene::MenuScene()
{
}

MenuScene::~MenuScene()
{
}
void MenuScene::Init(HWND* wnd, Input* in, float* dt, HDC hdc, HGLRC hrc, HGLRC hrc2)
{
	InitHelper(wnd, in, dt);
	hdc_ = hdc;
	hrc_ = hrc;
	hrc2_ = hrc2;
	scene_to_load_ = OPTIONS_SCENE;

	//////// Lighting
	glDisable(GL_LIGHTING);
	title_ = "Loading Scene";

	/////// Textures 
	//cameras
	camera_manager_.Init(input_, dt, &screenRect, hwnd_);
	camera_manager_.CreateCamera(FIXED_POSITION, "fixed one");
	camera_manager_.ChangeCamera("fixed one");
	camera_manager_.CurrentCamera()->SetPosition(Vector3(0, 0, 10));

	loading_screen_.Init(10, 1, "Textures/menu.png");
	loading_screen_.SetScale(150, 90, 1);



	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

}

void MenuScene::Update()
{
	SharedControls();
	camera_manager_.Update();
	

	Render();
}
void MenuScene::Render()
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
void MenuScene::ThreadFucntion(HDC	hdc, HGLRC hrc, HGLRC hrc2)
{
	HGLRC temp = wglGetCurrentContext();
	wglMakeCurrent(hdc, hrc2);
	temp = wglGetCurrentContext();

	wglMakeCurrent(NULL, NULL);
}