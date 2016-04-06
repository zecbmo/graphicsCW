#include "TronScene.h"

void TronScene::Init(HWND * hwnd, Input * in, float * dt)
{
	InitHelper(hwnd, in, dt);
	scene_to_load_ = TRON_SCENE;
	title_ = "Tron 3.0 : beta alpha 9";

	sky_box_.InitCubeBox("Textures/tronsky.png", "Textures/tronsky.png", "Textures/tronsky.png", "Textures/tronsky.png", "Textures/tronsky.png", "Textures/tronsky.png");
	sky_box_.SetMoving(true);

	light_.Init(GL_LIGHT0, POINT_LIGHT);
	light_.SetPosition(10, 10, 10);
	light_.Debug(true);

	light_.SetAllAttenuations(1, 0, 0); //a light with no fall off

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

	arena_.Init(Vector3(0, 0.01, 63));

	cone_.Init(2, 20, "Textures/cone.png");
	cone_.SetRotation(90, 0, 0);
	cone_.SetScale(1.5, 1.5, 1.5);

	light_beam_centres_.Init(60, 60, "Textures/troncylinder.png");
	light_beam_centres_.SetScale(1, 1, 10);
	light_beam_centres_.SetRotation(-90, 0, 0);
	light_beam_outers_.GetMaterial()->SetAllValues(1, 1, 1, 1);

	light_beam_centres_.GetMaterial()->SetShininess(50);

	light_beam_outers_.Init(60, 60, "Textures/troncylinder2.png");
	light_beam_outers_.SetScale(1.1, 1, 10);
	light_beam_outers_.SetRotation(-90, 0, 0);
	light_beam_outers_.GetMaterial()->SetAllValues(1, 1, 1, 1);
	light_beam_outers_.GetMaterial()->SetShininess(50);

	light_beam_centres_.SetMoving(true);
	light_beam_outers_.SetMoving(true);

	wall_pannel_.Init(2,1, "Textures/tronpannel.png");
	wall_display_.Init(4, 1, "Textures/tronwallpic.png");
	wall_display_.GetMaterial()->SetAlpha(0.75);
	wall_display_2_.Init(2, 1, "Textures/tronGlow.png");

	blue_box_.Init("Textures/box.png");
	blue_box_.GetMaterial()->SetColour(Colour_RGBA(0, 0.5, 1, 1));
	blue_box_.SetScale(1.5, 1.5, 1.5);
	red_box_.Init("Textures/box.png");
	red_box_.GetMaterial()->SetColourByTemplate(RED);
	red_box_.SetScale(1.5, 1.5, 1.5);

	railings_.Init("Textures/tronsquare.png");
	railings_.GetMaterial()->SetColourByTemplate(BLUE);

	railings_setter_.Init("Textures/tronsquare.png");
	railings_setter_.GetMaterial()->SetColourByTemplate(BLUE);


	mcp_base_.Init(60, 1,"Textures/box.png");
	mcp_base_.SetPosition(Vector3(24.16, 0.86, 0.34));
	mcp_base_.SetRotation(-90, 0, 0);
	mcp_base_.SetScale(5.16, 5.16, 1.18);
	mcp_base_.GetMaterial()->SetColour(Colour_RGBA(0.5,0.3,0.3,1));

	mcp_cylinder_.Init(60, 5, "Textures/troncylinder.png");
	mcp_cylinder_.SetMoving(true);
	mcp_cone_.Init(2,60, "Textures/troncylinder.png");
	mcp_cone_.GetMaterial()->SetColourByTemplate(WHITE);
	mcp_cone_.SetRotation(-90,0,0);
	mcp_cone_.SetMoving(true);
	mcp_.Init(60, 1, "Textures/mcp.png");
	mcp_.SetPosition(Vector3(24, 12, 0.34));
	mcp_.SetRotation(90, 0, 0);	
	mcp_.SetScale(4, 4, 4);
	mcp_.GetMaterial()->SetColour(Colour_RGBA(1,0.25,0.25,0.75));

	recogniser_.Init(1);
	recogniser_.SetPosition(Vector3(-5.16, 0, 61));


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

	light_beam_centres_.Update(0.2, *dt_);
	light_beam_outers_.Update(-0.1, *dt_);

	mcp_cylinder_.Update(10, *dt_);
	mcp_cone_.Update(10, *dt_);


	arena_.Update(*dt_);

	if (input_->IsKeyDown('7'))
	{
		scene_to_load_ = TESTING_SCENE;
	}
	///////////////////////////////////mover
	GameObjectMover(recogniser_);
	////////////////////////////////
	Render();
}

void TronScene::Render()
{

	uv_speed_ = 0.01 * (*dt_);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);// Clear The Screen And The Depth Buffer
	glLoadIdentity();// load Identity Matrix
	camera_manager_.Render();
	sky_box_.Render(camera_manager_.CurrentCamera()->GetPosition(), uv_speed_);	

	light_.Render();
	DrawFloors();
	DrawStartingRoom();
	DrawBoxes();
	DrawRailings();
	DrawMCP();
	recogniser_.Render();



	//railings_setter_.Render();

	arena_.Render();
	DrawWallPictures();		
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

	//DrawCorridor();


	//floor_.SetPosition(Vector3(70, 0, 0));
	////floor_.Render();

	glPushMatrix();
	glRotatef(-90, 0, 1, 0);
	DrawCorridor();
	glPopMatrix();

	//floor_.SetPosition(Vector3(0, 0, 70));
	//floor_.Render();

	//glPushMatrix();
	//glTranslatef(70, 0, 70);
	//glRotatef(180, 0, 1, 0);
	//DrawCorridor();
	//glPopMatrix();


}
void TronScene::DrawWall()
{
	glPushMatrix();
	glTranslatef(-25, 3.4, 12);
	light_beam_centres_.Render();
	glPopMatrix();


	glPushMatrix();
	glTranslatef(-25, 1.08, 12);
	cone_.Render();
	glPopMatrix();


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

	glEnable(GL_BLEND);
	glPushMatrix();
	glTranslatef(-25, 3.4, 12);
	light_beam_outers_.Render();
	glPopMatrix();
	glDisable(GL_BLEND);

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
void TronScene::DrawWallPictures()
{
	glEnable(GL_BLEND);
	glDisable(GL_LIGHTING);
	glPushMatrix();
	glTranslatef(-23.9, 3.92, -7.36);
	glRotatef(90, 0, 1, 0);
	wall_pannel_.Render();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(16.08, 5.04,-23.9);
	wall_pannel_.Render();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-3.5, 3.32, 24.8);
	wall_pannel_.Render();
	glPopMatrix();


	glPushMatrix();
	glTranslatef(6.5, 3.32, 24.8);
	wall_display_.Render();
	glPopMatrix();


	glPushMatrix();
	glTranslatef(-6.5, 3.32, 24.8);
	glRotatef(180, 0, 1, 0);
	wall_display_.Render();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-23.9, 3.20, -18.81);
	glRotatef(90, 0, 1, 0);
	wall_display_.Render();
	glPopMatrix();


	glPushMatrix();
	glTranslatef(18.63, 4.88, -23.9);
	wall_display_2_.Render();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-15.72, 2.2, -23.9);
	wall_display_2_.Render();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-15.72, 4.9, -23.9);
	wall_display_2_.Render();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-23.9, 5.4, 7.96);
	glRotatef(90, 0, 1, 0);
	wall_display_2_.Render();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-6.4, 3.6, -23.9);
	wall_display_2_.SetScale(-5.74, -5.74, -5.74);
	wall_display_2_.Render();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-23.9, 14.01, 19.22);
	glRotatef(90, 0, 1, 0);
	wall_display_.SetScale(7.96, 7.96, 7.96);
	wall_display_.Render();
	glPopMatrix();
	

	glDisable(GL_BLEND);
	glEnable(GL_LIGHTING);


	//reset scales
	wall_display_.SetScale(4,4,4);
	wall_display_2_.SetScale(2.8, 2.8, 2.8);
}
void TronScene::DrawBoxes()
{
	
	glPushMatrix();
	glTranslatef(-23, 0.75, -4);

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			for (int k = 0; k < 6; k++)
			{
				if ((i + j + k) % 5 == 0)
				{
					glPushMatrix();
					glTranslatef(i * 2, j * 2, k * 2);
					blue_box_.Render();
					glPopMatrix();

				}
				if ((i + j)% 5 == 0)
				{
					glPushMatrix();
					glTranslatef(i * 2, j * 2, k * 2);
					blue_box_.Render();
					glPopMatrix();
				}
			}
		}
	}
	glPopMatrix();



	glPushMatrix();
	glTranslatef(15, 0.75, 13);

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			for (int k = 0; k < 6; k++)
			{
				if ((i + j + k) % 6 == 1)
				{
					glPushMatrix();
					glTranslatef(i * 2, j * 2, k * 2);
					blue_box_.Render();
					glPopMatrix();

				}
				if ((i + j) % 6 == 0)
				{
					glPushMatrix();
					glTranslatef(i * 2, j * 2, k * 2);
					blue_box_.Render();
					glPopMatrix();
				}
			}
		}
	}
	glPopMatrix();

	DrawRedBoxes();
}
void TronScene::DrawRedBoxes()
{
	glPushMatrix();
	glTranslatef(-20, 0.75, -2);
	red_box_.Render();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-20, 4.5, 8);
	red_box_.Render();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-17.5, 11.75, -4);
	red_box_.Render();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-23.25, 0.75, -23.25);
	red_box_.Render();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(17, 4.25, 15);
	red_box_.Render();
	glPopMatrix();
}

void TronScene::DrawRailings()
{
	glPushMatrix();
	glTranslatef(-14.21, 0, 24.72);
	glScalef(23.35, 0.6 , 2.04);
	railings_.Render();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(14, 0, 24.72);
	glScalef(23.35, 0.6, 2.04);
	railings_.Render();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-4.89, 0.44, 24.58);
	glScalef(0.31, 1.64, 0.36);
	railings_.Render();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-8.89, 0.44, 24.58);
	glScalef(0.31, 1.64, 0.36);
	railings_.Render();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-12.89, 0.44, 24.58);
	glScalef(0.31, 1.64, 0.36);
	railings_.Render();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-16.89, 0.44, 24.58);
	glScalef(0.31, 1.64, 0.36);
	railings_.Render();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-20.89, 0.44, 24.58);
	glScalef(0.31, 1.64, 0.36);
	railings_.Render();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(4.89, 0.44, 24.58);
	glScalef(0.31, 1.64, 0.36);
	railings_.Render();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(8.89, 0.44, 24.58);
	glScalef(0.31, 1.64, 0.36);
	railings_.Render();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(12.89, 0.44, 24.58);
	glScalef(0.31, 1.64, 0.36);
	railings_.Render();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(16.89, 0.44, 24.58);
	glScalef(0.31, 1.64, 0.36);
	railings_.Render();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(20.89, 0.44, 24.58);
	glScalef(0.31, 1.64, 0.36);
	railings_.Render();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-13.25, 1.43, 24.57);
	glScalef(20.20, 0.45, 0.4);
	railings_.Render();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(13.25, 1.43, 24.57);
	glScalef(20.20, 0.45, 0.4);
	railings_.Render();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(2.4, 0, 34.23);
	glScalef(1, 0.7, 21.33);
	railings_.Render();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-2.4, 0, 34.23);
	glScalef(1, 0.7, 21.33);
	railings_.Render();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(25.3, -0.16, 14.50);
	glScalef(1.08, 1 , 22.51);
	railings_.Render();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(25.3, -0.16, -13.91);
	glScalef(1.08, 1, 22.51);
	railings_.Render();
	glPopMatrix();

	railings_.GetMaterial()->SetColourByTemplate(RED);
	glPushMatrix();
	glTranslatef(24.16, 0.38, 0);
	glScalef(13.56, 1, 11.95);
	railings_.Render();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(24.16, 15, 0);
	glScalef(13.56, 1, 11.95);
	railings_.Render();
	glPopMatrix();

	railings_.GetMaterial()->SetColourByTemplate(BLUE);

}

void TronScene::DrawMCP()
{
	
	mcp_base_.Render();

	glDisable(GL_LIGHTING);
	glPushMatrix();
	glTranslatef(24.16, -2, 0.34);
	glRotatef(-90, 1, 0, 0);
	glScalef(4, 4, 1);
	mcp_cylinder_.Render();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(24.16, 6.9, 0.34);
	glRotatef(-90, 1, 0, 0);
	glScalef(4, 4, 1.5);
	mcp_cylinder_.Render();
	glPopMatrix();

	


	glPushMatrix();
	glTranslatef(24.16, 4.94, 0.32);
	mcp_cone_.SetScale(4, 4, 1);
	mcp_cone_.Render();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(24.16, 4.94, 0.32);
	mcp_cone_.SetScale(4, 4, -1);
	mcp_cone_.Render();
	glPopMatrix();

	glEnable(GL_BLEND);
	mcp_.Render();
	glDisable(GL_BLEND);

	glEnable(GL_LIGHTING);

}
