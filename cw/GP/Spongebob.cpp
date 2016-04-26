#include "Spongebob.h"




SpongebobScene::SpongebobScene()
{
}

SpongebobScene::~SpongebobScene()
{
}
void SpongebobScene::Init(HWND* wnd, Input* in, float* dt, HDC	hdc, HGLRC hrc, HGLRC hrc2)
{
	InitHelper(wnd, in, dt);
	hdc_ = hdc;
	hrc_ = hrc;
	hrc2_ = hrc2;
	scene_to_load_ = SPONGEBOB;

	//////// Lighting
	glEnable(GL_LIGHTING);
	light_.Init(GL_LIGHT0, DIRECTIONAL_LIGHT);
	//light_.SetColourByTemplate(BLUE);
	light_.SetPosition(Vector3(20.0f, 10.0f, 10.0f));
	light_.SetAllValues(1, 1, 1, 1);
	light_.ResetAmbientToZero();

	camera_manager_.Init(input_, dt, &screenRect, hwnd_);
	
	camera_manager_.CreateCamera(FLOATING, "fps one");
	
	//fixed
	

	//fps
	camera_manager_.GetCamera("fps one")->SetPosition(Vector3(0, 3, 10));
	camera_manager_.GetCamera("fps one")->SetSensitivity(100, 100);
	camera_manager_.GetCamera("fps one")->SetAllSpeeds(10, 10, 10, 10);
	camera_manager_.ChangeCamera("fps one");
	




	//disc_.CreateShape(CUBE_CT);



	//camera_manager_.GetCamera("floating one")->SetSensitivity(5);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);


}
void SpongebobScene::ThreadFucntion(HDC	hdc, HGLRC hrc, HGLRC hrc2)
{
	HGLRC temp = wglGetCurrentContext();
	wglMakeCurrent(hdc, hrc2);
	temp = wglGetCurrentContext();

	sky_box_.Init(CUBE_SKY, "Textures/skybox_day.png");

	title_ = "Bikini Bottom";




	//std::string temp = SOIL_last_result();

	floor_.Init(100, 50, "Textures/sea.png");

	palm_.Load("Models/palm.obj", "Models/palm.png");
	float palm_scale = 0.005;
	palm_.SetScale(palm_scale, palm_scale, palm_scale);

	pineapple_.Load("Models/pine.obj", "Models/pineapple.png");
	pineapple_.SetPosition(Vector3(-3.34, 0.46, -5.32));
	pineapple_.SetScale(1.71, 1.71, 1.71);

	patrick_.Load("Models/patrick.obj", "Models/patrick.png");
	patrick_.SetPosition(Vector3(-2.69, 1.21, -2.71));
	patrick_.SetRotation(0, -15.87, 0);

	spongebob_.Load("Models/spongebob.obj", "Models/spongebob.png");
	spongebob_.SetPosition(Vector3(-4.27, 1.20, -2.54));
	spongebob_.SetRotation(0, 30.48, 0);

	gary_.Load("Models/gary.obj", "Models/gary.png");
	gary_.SetPosition(Vector3(-3.38, 1.20, -1.76));
	
	beach_one_.Init("Textures/sand.png");	
	beach_two_.Init("Textures/sand.png");	
	beach_three_.Init("Textures/sand.png");

	beach_one_.SetPosition(Vector3(-3.06, -0.41, -1.16));
	beach_one_.SetScale(16.18, 1.62, 10.36);

	beach_two_.SetPosition(Vector3(-13.19, 1.01, -12.32));
	beach_two_.SetScale(9.63, 6, 9.98);

	beach_three_.SetPosition(Vector3(2.2, 0.4, -12.06));
	beach_three_.SetScale(6.72, 2.14, 9.45);

	wglMakeCurrent(NULL, NULL);
}
void SpongebobScene::Update()
{
	SharedControls();
	camera_manager_.Update();

	// Do important update here
	
		
	

	//GameObjectMover(palm_);


	Render();
}

void SpongebobScene::Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);// Clear The Screen And The Depth Buffer
	glLoadIdentity();// load Identity Matrix




					 //Camera
	camera_manager_.Render();
	sky_box_.Render(camera_manager_.CurrentCamera()->GetPosition());
	
	light_.Render();
	//light_.Debug(true);

	beach_one_.Render();
	beach_two_.Render();
	beach_three_.Render();
	patrick_.Render();
	spongebob_.Render();
	pineapple_.Render();
	gary_.Render();

	palm_.SetPosition(Vector3(-12.71, 0 , -1.44));
	palm_.SetRotation(0, 0, 0);
	palm_.Render();
	palm_.SetPosition(Vector3(-12.5,0, -0.15));
	palm_.SetRotation(0,37.3 , 0);
	palm_.Render();
	palm_.SetPosition(Vector3(-11.77,0,-0.68));
	palm_.SetRotation(0,120.43 , 0);
	palm_.Render();

	glPushMatrix();
	glTranslatef(19, 0, 2);
	palm_.SetPosition(Vector3(-12.71, 0, -1.44));
	palm_.SetRotation(0, 0, 0);
	palm_.Render();
	palm_.SetPosition(Vector3(-12.5, 0, -0.15));
	palm_.SetRotation(0, 37.3, 0);
	palm_.Render();
	palm_.SetPosition(Vector3(-11.77, 0, -0.68));
	palm_.SetRotation(0, 120.43, 0);
	palm_.Render();
	glPopMatrix();


	glPushMatrix();
	glTranslatef(14, 2, -9);
	palm_.SetPosition(Vector3(-12.71, 0, -1.44));
	palm_.SetRotation(0, 0, 0);
	palm_.Render();
	palm_.SetPosition(Vector3(-12.5, 0, -0.15));
	palm_.SetRotation(0, 37.3, 0);
	palm_.Render();
	palm_.SetPosition(Vector3(-11.77, 0, -0.68));
	palm_.SetRotation(0, 120.43, 0);
	palm_.Render();
	glPopMatrix();

	glDisable(GL_LIGHTING);
	floor_.Render();	
	glEnable(GL_LIGHTING);

	//DisplayHUD(camera_manager_.CurrentCamera());
	SwapBuffers(hdc_);// Swap the frame buffers.
}


