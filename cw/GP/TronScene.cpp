#include "TronScene.h"

void TronScene::Init(HWND * hwnd, Input * in, float * dt)
{
	InitHelper(hwnd, in, dt);
	scene_to_load_ = TRON_SCENE;
	title_ = "Tron 3.0 : beta alpha 9";

	sky_box_.Init(CUBE_SKY, "Textures/tronsky.png");
	sky_box_.InitCubeBox("Textures/tronsky.png", "Textures/tronsky.png", "Textures/tronsky.png", "Textures/tronsky.png", "Textures/tronsky.png", "Textures/tronsky.png");
	

	light_.Init(GL_LIGHT0, DIRECTIONAL_LIGHT);
	light_.SetPosition(10, 10, 10);
	light_.Debug(true);
	camera_manager_.Init(input_, dt, &screenRect, hwnd_);
	camera_manager_.CreateCamera(FIRST_PERSON, "main");
	camera_manager_.GetCamera("main")->SetPosition(Vector3(0, 2, 0));
	camera_manager_.GetCamera("main")->SetSensitivity(200, 200);
	camera_manager_.GetCamera("main")->SetAllSpeeds(20, 20, 20, 20);
	camera_manager_.ChangeCamera("main");

	floor_.Init(50, 10, "Textures/tronfloor.png");
	floor_.GetMaterial()->SetColour(Colour_RGBA(0, 0.25, 0.5, 1));
	corridor_.Init(5, 1, "Textures/tronfloor.png");
	corridor_.GetMaterial()->SetColour(Colour_RGBA(0, 0.25, 0.5, 1));

	wall_.Init(10);
	wall_two_.Init(12);
	light_base_.Init(Vector3(0,1.5,0));

	arena_.Init(Vector3(63, 0.01, 70));


	glEnable(GL_TEXTURE_2D);
	glEnable(GL_COLOR_MATERIAL);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

}

void TronScene::Update()
{
	SharedControls();
	camera_manager_.Update();

	if (input_->IsKeyDown('7'))
	{
		scene_to_load_ = TESTING_SCENE;
	}
	GameObjectMover(arena_);
	Render();
}

void TronScene::Render()
{

	uv_speed_ = 0.5 * (*dt_);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);// Clear The Screen And The Depth Buffer
	glLoadIdentity();// load Identity Matrix
	camera_manager_.Render();
	sky_box_.Render(camera_manager_.CurrentCamera()->GetPosition(), uv_speed_);
	

	light_.Render();
	DrawFloors();
	DrawStartingRoom();

	arena_.Render();
	
	
	DisplayHUD(camera_manager_.CurrentCamera());
	SwapBuffers(hdc);// Swap the frame buffers.
}

void TronScene::DrawCorridor()
{
	corridor_.SetPosition(Vector3(42.5, 0, 0));
	corridor_.Render();
	corridor_.SetPosition(Vector3(37.5, 0, 0));
	corridor_.Render();
	corridor_.SetPosition(Vector3(32.5, 0, 0));
	corridor_.Render();
	corridor_.SetPosition(Vector3(27.5, 0, 0));
	corridor_.Render();
}
void TronScene::DrawFloors()
{
	//four different rooms to be rendered
	//with corridors between them
	floor_.SetPosition(Vector3(0, 0, 0));
	floor_.Render();

	DrawCorridor();


	floor_.SetPosition(Vector3(70, 0, 0));
	floor_.Render();

	glPushMatrix();
	glRotatef(-90, 0, 1, 0);
	DrawCorridor();
	glPopMatrix();

	floor_.SetPosition(Vector3(0, 0, 70));
	floor_.Render();

	glPushMatrix();
	glTranslatef(70, 0, 70);
	glRotatef(180, 0, 1, 0);
	DrawCorridor();
	glPopMatrix();


}
void TronScene::DrawWall()
{



	glPushMatrix();
	glTranslatef(-25, 0, 24);
	wall_.Render();
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(-25, 0, 10);
	wall_.Render();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-25, 0, 0);
	wall_two_.Render();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-25, 0, 12);
	light_base_.Render();
	glPopMatrix();

}
void TronScene::DrawStartingRoom()
{
	DrawWall();

	glPushMatrix();
	glRotatef(-90, 0, 1 ,0);
	glScalef(1,1,-1);
	DrawWall();
	glPopMatrix();




}
