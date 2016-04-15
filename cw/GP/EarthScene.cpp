#include "EarthScene.h"

EarthScene::~EarthScene()
{
	cloud_noise_.WriteCollectedDataToFile();
}

void EarthScene::Init(HWND * hwnd, Input * in, float * dt, HDC	hdc, HGLRC hrc, HGLRC hrc2)
{
	InitHelper(hwnd, in, dt);
	hdc_ = hdc;
	hrc_ = hrc;
	hrc2_ = hrc2;
	scene_to_load_ = EARTH_SCENE;

	//////// Lighting
	glEnable(GL_LIGHTING);
	light_.Init(GL_LIGHT0, POINT_LIGHT);
	
	light_.SetPosition(Vector3(-80.0f, 25.0f, 0.0f));
	light_.SetAllValues(10, 10, 10, 1); //set to ten to compensate for per vertex lighting
	light_.SetAmbientColour(0, 0, 0, 1);
	light_.SetAllAttenuations(1, 0, 0);	

	//cameras
	camera_target_ = Vector3(0, 0, 0);
	camera_manager_.Init(input_, dt, &screenRect, hwnd_);	
	camera_manager_.CreateCamera(ROTATING, "main");
	camera_manager_.GetCamera("main")->SetRotatingType(ROTATE_TO_TARGET);
	camera_manager_.GetCamera("main")->SetPosition(Vector3(10, 3, 10));
	camera_manager_.GetCamera("main")->SetStrafeSpeed(10);
	camera_manager_.GetCamera("main")->SetTarget(&camera_target_);
	camera_manager_.ChangeCamera("main");
	/////// Textures 
	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	//material
	glEnable(GL_COLOR_MATERIAL);

	
}
void EarthScene::ThreadFucntion(HDC	hdc, HGLRC hrc, HGLRC hrc2)
{
	HGLRC temp = wglGetCurrentContext();
	wglMakeCurrent(hdc, hrc2);
	temp = wglGetCurrentContext();
	earth_texture_ = SOIL_load_OGL_texture
		(
		"Textures/earth.bmp",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB |
		SOIL_FLAG_COMPRESS_TO_DXT

		);

	if (SOIL_last_result() == "Unable to open file")
	{
		error::ErrorMessage("Texture not loaded.");
	}

	sky_box_.InitCubeBox("Textures/skyFT.png", "Textures/skyLF.png", "Textures/skyRT.png", "Textures/skyBK.png", "Textures/skyUP.png", "Textures/skyDN.png");

	title_ = "Earth and Animated 3D noise clouds";
	cloud_noise_.GenerateNoise();
	//shapes
	sphere_.CreateShape(SPHERE, 40);
	sphere2_.CreateShape(SPHERE, 40);

	default_material_.Init(JADE, WHITE);
	default_material_.SetAmbientColour(0, 0, 0, 1);

	//movement vars
	earth_speed_ = 1;
	cloud_speed_ = 2;

	wglMakeCurrent(NULL, NULL);
}
void EarthScene::Update()
{
	SharedControls();
	camera_manager_.Update();
	
	

	Render();
}

void EarthScene::Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);// Clear The Screen And The Depth Buffer
	glLoadIdentity();// load Identity Matrix

	camera_manager_.Render();
	sky_box_.Render(camera_manager_.CurrentCamera()->GetPosition());
	light_.Render();
	light_.Debug(true);

	glBindTexture(GL_TEXTURE_2D, earth_texture_);
	default_material_.BindMaterial();
	
	earth_rot_ += earth_speed_*(*dt_);
	glRotatef(5, 1, 0, 0);
	glPushMatrix();
	glScalef(4, 4, 4);
	glRotatef(earth_rot_, 0, 1, 0);
	sphere_.Draw();
	glPopMatrix();


	GLuint cloud_texture = cloud_noise_.GetCloudNoiseTexture(*dt_);
	glEnable(GL_BLEND);
	glBindTexture(GL_TEXTURE_2D, cloud_texture);
	
	cloud_rot_ += cloud_speed_*(*dt_);
	glPushMatrix();
	glTranslatef(0, 0, 0);
	glRotatef(cloud_rot_, 0, 1, 0);
	glRotatef(160, 0, 1, 0);
	glScalef(4.02, 4.02, 4.02);
	sphere2_.Draw();
	glPopMatrix();

	glBindTexture(GL_TEXTURE_2D, NULL);
	glDisable(GL_BLEND);

	DisplayHUD(camera_manager_.CurrentCamera()); //im creating with how i rotate the camera in this scene, so this doesn't work properly :D
	SwapBuffers(hdc_);// Swap the frame buffers.



}
