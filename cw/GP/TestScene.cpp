#include "TestScene.h"




TestScene::TestScene()
{
}

TestScene::~TestScene()
{
}
void TestScene::Init(HWND* wnd, Input* in, float* dt, HDC	hdc, HGLRC hrc, HGLRC hrc2)
{
	InitHelper(wnd, in, dt);
	hdc_ = hdc;
	hrc_ = hrc;
	hrc2_ = hrc2;
	scene_to_load_ = TESTING_SCENE;
	
	//////// Lighting
	glEnable(GL_LIGHTING);
	light_.Init(GL_LIGHT0, POINT_LIGHT);
	
	light_point_.Init(GL_LIGHT1, POINT_LIGHT);
	light_point2_.Init(GL_LIGHT3, POINT_LIGHT);
	light_point3_.Init(GL_LIGHT4, POINT_LIGHT);
	light_point4_.Init(GL_LIGHT5, POINT_LIGHT);
	light_spot_.Init(GL_LIGHT2, SPOT_LIGHT);
	light_spot2_.Init(GL_LIGHT6, SPOT_LIGHT);


	light_.SetPosition(Vector3(0.0f, 10.0f, 0.0f));
	light_.SetAllValues(1, 1, 1, 1);
	light_.ResetAmbientToZero();
	
	


	light_point_.SetPosition(Vector3(20.0f, 3.0f, 0.0f));
	light_point_.SetAllValues(1, 1, 1, 1);
	light_point_.SetAllAttenuations(0.5, 0, 0.2);

	light_point2_.SetPosition(Vector3(20.0f, 3.0f, 5.0f));
	light_point2_.SetAllValues(1, 1, 1, 1);
	light_point2_.SetAllAttenuations(0.5, 0, 0.2);

	light_point3_.SetPosition(Vector3(20.0f, 3.0f, -5.0f));
	light_point3_.SetAllValues(1, 1, 1, 1);
	light_point3_.SetAllAttenuations(0.5, 0, 0.2);

	light_point4_.SetPosition(Vector3(-20.0f, 5.0f, 0.0f));
	light_point4_.SetAllValues(1, 1, 1, 1);
	light_point4_.SetAllAttenuations(0.5, 0, 0.1);


	light_spot_.SetPosition(Vector3(30.0f, 1.0f, 0.0f));
	light_spot_.SetAllValues(1, 1, 1, 1);
	light_spot_.SetSpotDirection(Vector3(1, 0, 0));
	light_spot_.SetAllAttenuations(0.5, 0, 0.2);
	light_spot_.SetSpotCutoff(20);
	light_spot_.SetSpotExponent(00);

	light_spot2_.SetPosition(Vector3(30.0f, 10.0f, 5.0f));
	light_spot2_.SetAllValues(1, 1, 1, 1);
	light_spot2_.SetSpotDirection(Vector3(0, -1, 0));
	light_spot2_.SetAllAttenuations(0.5, 0, 0.2);
	light_spot2_.SetSpotCutoff(20);
	light_spot2_.SetSpotExponent(0);
	/////// Textures 
	//cameras
	camera_manager_.Init(input_, dt, &screenRect, hwnd_);
	camera_manager_.CreateCamera(FIXED_POSITION, "fixed one");
	camera_manager_.CreateCamera(FIXED_POSITION, "fixed two");
	camera_manager_.CreateCamera(FLOATING, "fps one");
	camera_manager_.CreateCamera(ROTATING, "rot one");

	//fixed
	camera_manager_.ChangeCamera("fixed one");
	camera_manager_.CurrentCamera()->SetPosition(Vector3(0, 0, 10));

	//fps
	camera_manager_.GetCamera("fps one")->SetPosition(Vector3(0, 0, 10));
	camera_manager_.GetCamera("fps one")->SetSensitivity(100, 100);
	camera_manager_.GetCamera("fps one")->SetAllSpeeds(10, 10, 10, 10);

	//rotating 
	camera_manager_.GetCamera("rot one")->SetRotatingType(ANIMATED);
	camera_manager_.GetCamera("rot one")->SetStartPoint(Vector3(-10, 0, 0));
	camera_manager_.GetCamera("rot one")->SetEndPoint(Vector3(10, 0, 0));
	camera_manager_.GetCamera("rot one")->SetPosition(Vector3(0, 5, 10));
	camera_manager_.GetCamera("rot one")->SetTimeDelay(1.0f);
	camera_manager_.GetCamera("rot one")->SetRotationTime(4);


	
	sphere_.Init(Colour_RGBA(1,1,1,1));
	sphere_.GetMaterial()->SetDirectColourControl(true);
	
	//disc_.CreateShape(CUBE_CT);

	
	glEnable(GL_COLOR_MATERIAL);
	//camera_manager_.GetCamera("floating one")->SetSensitivity(5);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);


}
void TestScene::ThreadFucntion(HDC	hdc, HGLRC hrc, HGLRC hrc2)
{
	HGLRC temp = wglGetCurrentContext();
	wglMakeCurrent(hdc, hrc2);
	temp = wglGetCurrentContext();

	sky_box_.Init(CUBE_SKY, "Textures/skyUP.png");

	title_ = "Testing Scene";

	custom_.CreateShape(CUBE_ST);

	cloud_noise_.GenerateNoise();

	text = SOIL_load_OGL_texture
		(
		"Textures/crate.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB |
		SOIL_FLAG_COMPRESS_TO_DXT

		);
	//std::string temp = SOIL_last_result();
	int lklk = 0;
	floor_.Init(100,  "Textures/tronfloor.png");
	floor_.SetPosition(Vector3(-50, -1, -50));
	moveF = 0;
	moveR = 0;
	speed_ = 1;

	box_.Init("Textures/crate.png");
	MakeManyCubes();
	wglMakeCurrent(NULL, NULL);
}
void TestScene::Update()
{
	SharedControls();
	camera_manager_.Update();

	// Do important update here
	if (input_->IsKeyDown('6'))
	{
		camera_manager_.ChangeCamera("fixed two");
	}
	else if (input_->IsKeyDown('7'))
	{
		camera_manager_.ChangeCamera("fixed one");
	}
	else if (input_->IsKeyDown('8'))
	{
		camera_manager_.ChangeCamera("rot one");
	}
	else
	{
		camera_manager_.ChangeCamera("fps one");
	}
	
	RotateLight();

	if (timer_ > 1.0)
	{
		float r = RandomNumber(1, 100) / 100.0;
		float g = RandomNumber(1, 100) / 100.0;
		float b = RandomNumber(1, 100) / 100.0;

		light_point_.SetAllValues(Colour_RGBA(r, g, b, 1));

		r = RandomNumber(1, 100) / 100.0;
		g = RandomNumber(1, 100) / 100.0;
		b = RandomNumber(1, 100) / 100.0;
		light_point2_.SetAllValues(Colour_RGBA(r, g, b, 1));

		r = RandomNumber(1, 100) / 100.0;
		g = RandomNumber(1, 100) / 100.0;
		b = RandomNumber(1, 100) / 100.0;
		light_point3_.SetAllValues(Colour_RGBA(r, g, b, 1));
		timer_ = 0;
	}


	timer_ += *dt_;

	//light_spot_.SetSpotDirection(camera_manager_.CurrentCamera()->GetForwardVec());
	//light_spot_.SetPosition(camera_manager_.CurrentCamera()->GetPosition());


	//GameObjectMover(floor_);

	Render();
}

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
	light_.Debug(true);

	light_point_.Render();
	light_point_.Debug(true);

	light_point2_.Render();
	light_point2_.Debug(true);

	light_point3_.Render();
	light_point3_.Debug(true);

	light_point4_.Render();
	light_point4_.Debug(true);


	light_spot_.Render();
	light_spot_.Debug(true);

	light_spot2_.Render();
	light_spot2_.Debug(true);

	floor_.Render();
	

	
	DrawShadowMatrixScene();

	sphere_.GetMaterial()->SetMaterialByTemplate(JADE);
	sphere_.SetPosition(Vector3(-21, 2, 0));
	sphere_.Render();

	sphere_.GetMaterial()->SetMaterialByTemplate(PLASTIC);
	sphere_.SetPosition(Vector3(-21, 2, 2));
	sphere_.Render();


	sphere_.GetMaterial()->SetMaterialByTemplate(GOLD);
	sphere_.SetPosition(Vector3(-21, 2, -2));
	sphere_.Render();


	sphere_.GetMaterial()->SetMaterialByTemplate(BRONZE);
	sphere_.SetPosition(Vector3(-21, 2, 4));
	sphere_.Render();


	sphere_.GetMaterial()->SetMaterialByTemplate(COPPER);
	sphere_.SetPosition(Vector3(-21, 2, -4));
	sphere_.Render();

	sphere_.GetMaterial()->SetMaterialByTemplate(SILVER);
	sphere_.SetPosition(Vector3(-19, 2, 0));
	sphere_.Render();

	sphere_.GetMaterial()->SetMaterialByTemplate(TURQUOISE);
	sphere_.SetPosition(Vector3(-19, 2, 2));
	sphere_.Render();


	sphere_.GetMaterial()->SetMaterialByTemplate(RUBY);
	sphere_.SetPosition(Vector3(-19, 2, -2));
	sphere_.Render();


	sphere_.GetMaterial()->SetMaterialByTemplate(PEARL);
	sphere_.SetPosition(Vector3(-19, 2, 4));
	sphere_.Render();


	sphere_.GetMaterial()->SetMaterialByTemplate(OBSIDIAN);
	sphere_.SetPosition(Vector3(-19, 2, -4));
	sphere_.Render();
	glPushMatrix();
	glTranslatef(0, 10, 20);
	glCallList(cubes_);
	glPopMatrix();
//	DisplayHUD(camera_manager_.CurrentCamera());
	SwapBuffers(hdc_);// Swap the frame buffers.
}
void TestScene::DrawShadowMatrixScene()
{

	float rotation = 0;


	float x = light_.GetPosition().GetX();
	float y = light_.GetPosition().GetY();
	float z = light_.GetPosition().GetZ();


	GLfloat Light_Position[] = { x, y, z, 0 };

	// Activate light
	

	GLfloat v0[3], v1[3], v2[3];

	// To define a plane that matches the floor, we need to 3 vertices from it
	v0[0] = -1.0;
	v0[1] = -1.0;
	v0[2] = -1.0;

	v1[0] = -1.0;
	v1[1] = -1.0;
	v1[2] = 1.0;

	v2[0] = 1.0;
	v2[1] = -1.0;
	v2[2] = -1.0;


	// Build a shadow matrix using the light's current position and the plane
	GenerateShadowMatrix(matrix, Light_Position, v0, v1, v2);

	//draw floor
	//glBegin(GL_QUADS);
	//glNormal3f(0.0, 1.0, 0.0);
	//glVertex3f(-5.0, -1.0, -5.0);
	//glVertex3f(-5.0, -1.0, 5.0);
	//glVertex3f(5.0, -1.0, 5.0);
	//glVertex3f(5.0, -1.0, -5.0);
	//glEnd();

	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);

	glColor3f(0.1f, 0.1f, 0.1f); // Shadow's color
	glPushMatrix();
	glMultMatrixf((GLfloat *)matrix);
	//translate to floor and draw shadow, remember to match any transforms on the object
	glTranslatef(0, 1, 0);
	glRotatef(rotation, 0, 1, 0);
	
	//disc_.Draw();
	Material temp2;
	temp2.Init(GOLD, WHITE);
	glBindTexture(GL_TEXTURE_2D, text);
	custom_.Draw();
	glPopMatrix();

	glColor3f(1.0f, 1.0f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);

	//render object
	glPushMatrix();
	glTranslatef(0, 1, 0);
	glRotatef(rotation, 0, 1, 0);
	
	//disc_.Draw();
	glBindTexture(GL_TEXTURE_2D, text);
	custom_.Draw();
	glPopMatrix();
}

void TestScene::GenerateShadowMatrix(float matrix[16], float light_pos[4], GLfloat v0[3], GLfloat v1[3], GLfloat v2[3]) 
{

	//Defining vertices of plane are PQR with edges PQ and PR
	Vector3 P(v0[0], v0[1], v0[2]);
	Vector3 Q(v1[0], v1[1], v1[2]);
	Vector3 R(v2[0], v2[1], v2[2]);

	Vector3 PQ = Q - P;
	PQ.Normalise();
	Vector3 PR = R - P;
	PR.Normalise();
	Vector3 normal = PR.Cross(PQ);

	//Equation of plane is ax + by + cz = d
	//a, b and c are the coefficients of the normal to the plane (i.e. normal = ai + bj + ck)
	//If (x0, y0, z0) is any point on the plane, d = a*x0 + b*y0 + c*z0
	//i.e. d is the dot product of any point on the plane (using P here) and the normal to the plane
	float a, b, c, d;
	a = normal.GetX();
	b = normal.GetY();
	c = normal.GetZ();
	d = normal.Dot(P);

	//Origin of projection is at x, y, z. Projection here originating from the light source's position
	float x, y, z;

	x = light_pos[0];
	y = light_pos[1];
	z = light_pos[2];

	//This is the general perspective transformation matrix from a point (x, y, z) onto the plane ax + by + cz = d
	matrix[0] = d - (b * y + c * z);
	matrix[1] = a * y;
	matrix[2] = a * z;
	matrix[3] = a;

	matrix[4] = b * x;
	matrix[5] = d - (a * x + c * z);
	matrix[6] = b * z;
	matrix[7] = b;

	matrix[8] = c * x;
	matrix[9] = c * y;
	matrix[10] = d - (a * x + b * y);
	matrix[11] = c;

	matrix[12] = -d * x;
	matrix[13] = -d * y;
	matrix[14] = -d * z;
	matrix[15] = -(a * x + b * y + c * z);
}
void TestScene::RotateLight()
{
	GLdouble cX = 0;      // x coordinate of circle center
	GLdouble cY = 0;
	GLdouble cZ = 0;     // y coordinate of circle center
						 //GLdouble step = 15;  // amount to add to theta each time (degrees)
	GLdouble radius = 10;


	//	move = move*6.28;
	//	moveR = moveR*3.14;

	GLdouble X = cX + (radius*cos(moveF*6.28))*(sin(moveR*6.28));
	GLdouble Y = cY + (radius*sin(moveF*6.28))*(sin(moveR*6.28));

	GLdouble Z = cZ + radius*cos(moveR*6.28);

	GLdouble fakePI = 3.14 / 180;

	if (input_->IsKeyDown(VK_RIGHT))
	{

		moveR += speed_**dt_;

	}
	if (input_->IsKeyDown(VK_LEFT))
	{
		moveR -= speed_**dt_;

	}


	light_.SetPosition(Vector3(X, 10, Z));

}
int TestScene::RandomNumber(int min, int max)
{
	
	return min+ rand()%(max -min);
}
void TestScene::MakeManyCubes()
{


	cubes_ = glGenLists(1);
	glNewList(cubes_, GL_COMPILE);

	glMatrixMode(GL_MODELVIEW);

	for (int j = -10; j < 10; j += 2)
	{
		for (int i = -10; i < 10; i += 2)
		{
			for (int k = -10; k < 10; k += 2)
			{
				glPushMatrix();
				glTranslatef(i * 1, k * 1, j * 1);


				glPushMatrix();
				box_.Render();
				glPopMatrix();
						
			}

		}
	}


	glEndList();

}