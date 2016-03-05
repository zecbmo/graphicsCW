#include "TestScene.h"

TestScene::TestScene()
{
}

TestScene::~TestScene()
{
}
void TestScene::Init(HWND* wnd, Input* in, float* dt)
{
	InitHelper(wnd, in, dt);

	scene_to_load_ = TESTING_SCENE;

	//////// Lighting
	glEnable(GL_LIGHTING);
	light_.Init(GL_LIGHT0, DIRECTIONAL_LIGHT);
	//light_.SetColourByTemplate(BLUE);
	light_.SetPosition(Vector3(-2.0f, 0.0f, 0.0f));
	light_.SetAllValues(1, 1, 1, 1);
	light_.ResetAmbientToZero();
	/////// Materials 
	//glEnable(GL_COLOR_MATERIAL);

	/////// Textures 


	//cameras

	camera_manager_.Init(input_, dt, &screenRect, hwnd_);

	camera_manager_.CreateCamera(FIXED_POSITION, "fixed one");
	camera_manager_.CreateCamera(FIXED_POSITION, "fixed two");
	camera_manager_.CreateCamera(FIRST_PERSON, "fps one");
	camera_manager_.CreateCamera(ROTATING, "rot one");



	//fixed
	camera_manager_.ChangeCamera("fixed one");
	camera_manager_.CurrentCamera()->SetPosition(Vector3(0, 0, -10));

	//fps
	camera_manager_.GetCamera("fps one")->SetPosition(Vector3(10, 0, 10));
	camera_manager_.GetCamera("fps one")->SetSensitivity(10, 10);
	camera_manager_.GetCamera("fps one")->SetAllSpeeds(10, 10, 10, 10);

	//rotating 
	camera_manager_.GetCamera("rot one")->SetRotatingType(ANIMATED);
	camera_manager_.GetCamera("rot one")->SetStartPoint(Vector3(-10, 0, 0));
	camera_manager_.GetCamera("rot one")->SetEndPoint(Vector3(10, 0, 0));
	camera_manager_.GetCamera("rot one")->SetPosition(Vector3(0, 5, 10));
	camera_manager_.GetCamera("rot one")->SetTimeDelay(1.0f);
	camera_manager_.GetCamera("rot one")->SetRotationTime(4);









	int thisnUmber = 0;

	//camera_manager_.GetCamera("floating one")->SetSensitivity(5);
}

void TestScene::Update()
{
	camera_manager_.Update();

	// Do important update here
	if (input_->IsKeyDown('1'))
	{
		camera_manager_.ChangeCamera("fixed two");
	}
	else if (input_->IsKeyDown('2'))
	{
		camera_manager_.ChangeCamera("fixed one");
	}
	else if (input_->IsKeyDown('3'))
	{
		camera_manager_.ChangeCamera("rot one");
	}
	else
	{
		camera_manager_.ChangeCamera("fps one");
	}

	if (input_->IsKeyDown('9'))
	{
		scene_to_load_ = BASE_SCENE;
	}




	Render();
}

void TestScene::Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);// Clear The Screen And The Depth Buffer
	glLoadIdentity();// load Identity Matrix

					 //Camera

	camera_manager_.Render();
	//Light done first	
	light_.Render();

	//light_.Render();

	Material temp;

	temp.Init(EMERALD, BLACK);
	temp.SetDirectColourControl(true);

	temp.BindMaterial();
	glPushMatrix();
	glTranslatef(-5, 0, 0);
	gluSphere(gluNewQuadric(), 1, 20, 20);
	glPopMatrix();

	temp.SetMaterialByTemplate(JADE);

	temp.SetColourByTemplate(BROWN);
	temp.BindMaterial();
	glPushMatrix();
	glTranslatef(-2.5, 0, 0);
	gluSphere(gluNewQuadric(), 1, 20, 20);
	glPopMatrix();

	temp.SetMaterialByTemplate(PLASTIC);
	temp.SetColour(Colour_RGBA(1, 0, 1, 1));
	temp.SetDirectColourControl(false);
	temp.BindMaterial();

	glPushMatrix();
	glTranslatef(0, 0, 0);
	gluSphere(gluNewQuadric(), 1, 20, 20);
	glPopMatrix();


	temp.SetMaterialByTemplate(RUBY);
	temp.SetColourByTemplate(ORANGE);

	temp.BindMaterial();

	glPushMatrix();
	glTranslatef(2.5, 0, 0);
	gluSphere(gluNewQuadric(), 1, 20, 20);
	glPopMatrix();

	temp.SetMaterialByTemplate(PEWTER);
	temp.SetColourByTemplate(BLACK);

	temp.BindMaterial();

	glPushMatrix();
	glTranslatef(5, 0, 0);
	gluSphere(gluNewQuadric(), 1, 20, 20);
	glPopMatrix();


	//Render HUD last

	SwapBuffers(hdc);// Swap the frame buffers.
}
