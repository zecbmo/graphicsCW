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
	sky_box_.Init(CUBE_SKY, "Textures/stars.png");

	/////// Textures 
	//cameras
	camera_manager_.Init(input_, dt, &screenRect, hwnd_);
	camera_manager_.CreateCamera(FIXED_POSITION, "fixed one");
	camera_manager_.CreateCamera(FIXED_POSITION, "fixed two");
	camera_manager_.CreateCamera(FLOATING, "fps one");
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



	
	disc_.CreateShape(CUBE_CT);

	
	cloud_noise_.GenerateNoise();

	text = SOIL_load_OGL_texture
		(
			"Textures/day_skybox.png",
			SOIL_LOAD_AUTO,
			SOIL_CREATE_NEW_ID,
			SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB |
			SOIL_FLAG_COMPRESS_TO_DXT

			);
	std::string temp = SOIL_last_result();
	int lklk = 0;
	//camera_manager_.GetCamera("floating one")->SetSensitivity(5);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

}

void TestScene::Update()
{
	SharedControls();
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

	if (input_->IsKeyDown('0'))
	{
		scene_to_load_ = EARTH_SCENE;
	}


	Render();
}
float rot = 0;
void TestScene::Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);// Clear The Screen And The Depth Buffer
	glLoadIdentity();// load Identity Matrix

	


					 //Camera
	camera_manager_.Render();
	sky_box_.Render(camera_manager_.CurrentCamera()->GetPosition());
	//Light done first	
	int tempNm = GL_LIGHT0;
	light_.Render();
	//glDisable(GL_LIGHTING);
	GLUquadricObj *qObj = gluNewQuadric();
	gluQuadricNormals(qObj, GLU_SMOOTH);
	gluQuadricTexture(qObj, GL_TRUE);
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

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, text);
	temp.SetMaterialByTemplate(PLASTIC);
	temp.SetColour(Colour_RGBA(1, 1, 1, 1));
	temp.SetDirectColourControl(false);
	temp.BindMaterial();

	glPushMatrix();
	glTranslatef(0, 2, 0);
	gluSphere(qObj, 1, 40, 40);
	glPopMatrix();


	temp.SetMaterialByTemplate(RUBY);
	temp.SetColourByTemplate(ORANGE);

	temp.BindMaterial();

	glPushMatrix();
	glTranslatef(2.5, 0, 0);
	gluSphere(gluNewQuadric(), 1, 20, 20);
	glPopMatrix();

	
	temp.SetMaterialByTemplate(GOLD, WHITE);
	temp.BindMaterial();

	GLuint text2 = cloud_noise_.GetCloudNoiseTexture(*dt_);

	glDisable(GL_LIGHTING);
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, text);
	glTranslatef(5, 5, 0);
	glRotatef(-20, 0, 1, 0);
	glScalef(5, 5, 5);
	disc_.Draw();
	glPopMatrix();
	glEnable(GL_LIGHTING);

	
	

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glEnable(GL_BLEND);
	glBindTexture(GL_TEXTURE_2D, text2);


	

	rot+= 5 * *dt_;
	glPushMatrix();
	glTranslatef(0, 2, 0);
	glRotatef(rot, 0, 1, 0);
	glRotatef(90, 1, 0, 0);

	gluSphere(qObj, 1.004, 40, 40);
	glPopMatrix();

	glBindTexture(GL_TEXTURE_2D, NULL);
	glDisable(GL_BLEND);
	//Render HUD last

	SwapBuffers(hdc);// Swap the frame buffers.
}
