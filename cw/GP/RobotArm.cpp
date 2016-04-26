#include "RobotArm.h"

RobotScene::~RobotScene()
{

}

void RobotScene::Init(HWND * hwnd, Input * in, float * dt, HDC	hdc, HGLRC hrc, HGLRC hrc2)
{
	InitHelper(hwnd, in, dt);
	hdc_ = hdc;
	hrc_ = hrc;
	hrc2_ = hrc2;
	scene_to_load_ = ROBOT_ARM;
	
	camera_manager_.Init(input_, dt, &screenRect, hwnd_);
	camera_manager_.CreateCamera(FIXED_POSITION, "main");
	
	camera_manager_.GetCamera("main")->SetPosition(Vector3(0, 0,3));	
	camera_manager_.ChangeCamera("main");
	
	glEnable(GL_COLOR_MATERIAL);


}
void RobotScene::ThreadFucntion(HDC	hdc, HGLRC hrc, HGLRC hrc2)
{
	HGLRC temp = wglGetCurrentContext();
	wglMakeCurrent(hdc, hrc2);
	temp = wglGetCurrentContext();
	
	
	title_ = "Robot Arm";
	rotation = 0;
	rotation2 = 0;
	speed = 50.0;

	mainBodyRotZ = 0;
	mainBodyRotY = 0;
	forArmRot = 0;
	handRotZ = 0;
	handRotY = 0;
	digitRot[0] = 0;
	digitRot[1] = 0;
	digitRot[2] = 0;



	wglMakeCurrent(NULL, NULL);
}
void RobotScene::Update()
{
	SharedControls();
	camera_manager_.Update();


	if (input_->IsKeyDown('R') && mainBodyRotZ< 90)
	{
		mainBodyRotZ += (speed * 2)**dt_;
	}
	if (input_->IsKeyDown('F') && mainBodyRotZ > 0)
	{
		mainBodyRotZ -= (speed * 2)**dt_;
	}
	//if (input->isKeyDown(VK_NUMPAD6) && mainBodyRotY< 90)
	if (input_->IsKeyDown('A') && mainBodyRotY< 90)
	{
		mainBodyRotY += (speed * 2)**dt_;
	}
	//if (input->isKeyDown(VK_NUMPAD4) && mainBodyRotY > -90)
	if (input_->IsKeyDown('D') && mainBodyRotY > -90)
	{
		mainBodyRotY -= (speed * 2)**dt_;
	}

	if (input_->IsKeyDown('W') && forArmRot < 90)
	{
		forArmRot += speed**dt_;
	}
	if (input_->IsKeyDown('S') && forArmRot > 0)
	{
		forArmRot -= speed**dt_;
	}
	
	

	if (input_->IsKeyDown(VK_RIGHT) && handRotY < 80)
	{

		handRotY += speed* *dt_;
	}
	if (input_->IsKeyDown(VK_LEFT) && handRotY > -80)
	{
		handRotY -= speed* *dt_;
	}
	if (input_->IsKeyDown(VK_UP) && handRotZ < 80)
	{
		handRotZ += speed* *dt_;
	}
	if (input_->IsKeyDown(VK_DOWN) && handRotZ > -80)
	{
		handRotZ -= speed* *dt_;
	}

	if (input_->IsKeyDown('Q') && digitRot[0] < 125)
	{
		digitRot[0] += speed * *dt_;
		//input->SetKeyUp('Q');
	}
	else
	{
		if (digitRot[0] >= 0)
		{
			digitRot[0] -= speed  * *dt_;
		}

	}
	if (input_->IsKeyDown('E') && digitRot[1] < 125)
	{
		digitRot[1] += speed * *dt_;
		//input->SetKeyUp('Q');
	}
	else
	{
		if (digitRot[1] >= 0)
		{
			digitRot[1] -= speed  * *dt_;
		}

	}
	if (input_->IsKeyDown(VK_SPACE) && digitRot[2] < 125)
	{
		digitRot[2] += speed * *dt_;
		//input->SetKeyUp('Q');
	}
	else
	{
		if (digitRot[2] >= 0)
		{
			digitRot[2] -= speed  * *dt_;
		}

	}

	rotation += speed * *dt_;
	rotation2 += (speed * 2) * *dt_;

	Render();
}

void RobotScene::Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);// Clear The Screen And The Depth Buffer
	glLoadIdentity();// load Identity Matrix

	camera_manager_.Render();
	
	
	glTranslatef(-1.0f, 0.0f, 0.0f);
	glPushMatrix();
		glTranslatef(-1, -0.5, 0);
		glRotatef(mainBodyRotY, 0, 1, 0);
		glRotatef(mainBodyRotZ, 0, 0, 1);
		glScalef(0.3, 0.3, 0.3);
		glTranslatef(1, 0, 0);
		createCubeFromPoint(1.0, 0.5, 0.5); /////////////main body

		glPushMatrix();
			glTranslatef(1, 0.5, 0);
			glRotatef(forArmRot, 0, 0, 1);
			glTranslatef(1, -0.5, 0);
			createCubeFromPoint(1.0, 0.5, 0.5); //////////////////forarm

			glPushMatrix();
				//glTranslatef(1, 0.5, 0);
				glTranslatef(1.4, 0, 0);
				glRotatef(handRotZ, 0, 0, 1);
				glRotatef(handRotY, 0, 1, 0);
				//glTranslatef(1.35, 0, 0);

				gluSphere(gluNewQuadric(), 0.7, 20, 20); ////////////////////////hand


				glPushMatrix();
					glRotatef(-45, 0, 0, 1);
					glRotatef(30, 0, 1, 0);
					glRotatef(45, 1, 0, 0);
					glScalef(0.3, 0.3, 0.3);
					glTranslatef(3.2, 0, 0);
					createCubeFromPoint(1.0, 0.5, 0.5);           ///////////////////finger

					glPushMatrix();

						glTranslatef(1, 0.5, 0);
						glRotatef(digitRot[0], 0, 0, 1);
						glTranslatef(1, -0.5, 0);
						createCubeFromPoint(1.0, 0.5, 0.5);	 ///////////////////finger
						glPopMatrix();

					glPopMatrix();

					glPushMatrix();
						glRotatef(-45, 0, 0, 1);
						glRotatef(-30, 0, 1, 0);
						glScalef(0.3, 0.3, 0.3);
						glTranslatef(3.2, 0, 0);
						createCubeFromPoint(1.0, 0.5, 0.5);	 ///////////////////finger
						glPushMatrix();

							glTranslatef(1, 0.5, 0);
							glRotatef(digitRot[1], 0, 0, 1);
							glTranslatef(1, -0.5, 0);
							createCubeFromPoint(1.0, 0.5, 0.5);
						glPopMatrix();

					glPopMatrix();

					glPushMatrix();
						glRotatef(30, 0, 0, 1);
						glRotatef(180, 1, 0, 0);
						glScalef(0.3, 0.3, 0.3);
						glTranslatef(3.2, 0, 0);
						createCubeFromPoint(1.0, 0.5, 0.5);
						glPushMatrix();

							glTranslatef(1, 0.5, 0);
							glRotatef(digitRot[2], 0, 0, 1);
							glTranslatef(1, -0.5, 0);
							createCubeFromPoint(1.0, 0.5, 0.5);
						glPopMatrix();

				glPopMatrix();


			glPopMatrix();



		glPopMatrix();


	glPopMatrix();

	



	glBindTexture(GL_TEXTURE_2D, NULL);
	
	//glEnable(GL_LIGHTING);
	SwapBuffers(hdc_);// Swap the frame buffers.
	glDisable(GL_LIGHTING);
	

}
void RobotScene::createCubeFromPoint(float x, float y, float z)
{
	glBegin(GL_TRIANGLES);

	glColor3f(1.0, 0.0, 0.0); //front

	glVertex3f(x, y, z);
	glVertex3f(-x, y, z);
	glVertex3f(x, -y, z);

	glVertex3f(x, -y, z);
	glVertex3f(-x, y, z);
	glVertex3f(-x, -y, z);

	glColor3f(0.0, 1.0, 0.0); //right
	glVertex3f(x, y, z);
	glVertex3f(x, -y, z);
	glVertex3f(x, -y, -z);

	glVertex3f(x, y, z);
	glVertex3f(x, -y, -z);
	glVertex3f(x, y, -z);

	glColor3f(0.0, 1.0, 1.0); //top
	glVertex3f(-x, y, -z);
	glVertex3f(-x, y, z);
	glVertex3f(x, y, z);

	glVertex3f(-x, y, -z);
	glVertex3f(x, y, z);
	glVertex3f(x, y, -z);

	glColor3f(0.2, 0.2, 0.5); //left
	glVertex3f(-x, -y, -z);
	glVertex3f(-x, -y, z);
	glVertex3f(-x, y, -z);


	glVertex3f(-x, y, -z);

	glVertex3f(-x, y, z);
	glVertex3f(-x, -y, z);


	glColor3f(1.0, 0.0, 1.0); //back
	glVertex3f(-x, y, -z);
	glVertex3f(-x, -y, -z);
	glVertex3f(x, -y, -z);

	glVertex3f(-x, y, -z);
	glVertex3f(x, y, -z);
	glVertex3f(x, -y, -z);

	glColor3f(1.0, 1.0, 1.0); //bottom
	glVertex3f(x, -y, z);
	glVertex3f(-x, -y, z);
	glVertex3f(-x, -y, -z);

	glVertex3f(x, -y, z);
	glVertex3f(-x, -y, -z);
	glVertex3f(x, -y, -z);

	//}
	glEnd();

}