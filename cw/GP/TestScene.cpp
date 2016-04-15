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
	light_.Init(GL_LIGHT0, DIRECTIONAL_LIGHT);
	//light_.SetColourByTemplate(BLUE);
	light_.SetPosition(Vector3(0.0f, 10.0f, 0.0f));
	light_.SetAllValues(1, 1, 1, 1);
	light_.ResetAmbientToZero();
	/////// Materials 
	//glEnable(GL_COLOR_MATERIAL);

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


	

	
	//disc_.CreateShape(CUBE_CT);

	

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

	custom_.CreateShape(CUBE_CT);

	cloud_noise_.GenerateNoise();

	text = SOIL_load_OGL_texture
		(
		"Textures/day_skybox.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB |
		SOIL_FLAG_COMPRESS_TO_DXT

		);
	//std::string temp = SOIL_last_result();
	int lklk = 0;
	floor_.Init(1, 1, "Textures/tronfloor.png");

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
	light_.Debug(true);
	


	//glDisable(GL_LIGHTING);
	//GLUquadricObj *qObj = gluNewQuadric();
	//gluQuadricNormals(qObj, GLU_SMOOTH);
	//gluQuadricTexture(qObj, GL_TRUE);
	////light_.Render();

	//Material temp;

	//temp.Init(EMERALD, BLACK);
	//temp.SetDirectColourControl(true);

	//temp.BindMaterial();
	//glPushMatrix();
	//glTranslatef(-5, 0, 0);
	//gluSphere(gluNewQuadric(), 1, 20, 20);
	//glPopMatrix();

	//temp.SetMaterialByTemplate(JADE);

	//temp.SetColourByTemplate(BROWN);
	//temp.BindMaterial();
	//glPushMatrix();
	//glTranslatef(-2.5, 0, 0);
	//gluSphere(gluNewQuadric(), 1, 20, 20);
	//glPopMatrix();

	//glEnable(GL_TEXTURE_2D);
	//glBindTexture(GL_TEXTURE_2D, text);
	//temp.SetMaterialByTemplate(PLASTIC);
	//temp.SetColour(Colour_RGBA(1, 1, 1, 1));
	//temp.SetDirectColourControl(false);
	//temp.BindMaterial();

	//glPushMatrix();
	//glTranslatef(0, 2, 0);
	//gluSphere(qObj, 1, 40, 40);
	//glPopMatrix();


	//temp.SetMaterialByTemplate(RUBY);
	//temp.SetColourByTemplate(ORANGE);

	//temp.BindMaterial();

	//glPushMatrix();
	//glTranslatef(2.5, 0, 0);
	//gluSphere(gluNewQuadric(), 1, 20, 20);
	//glPopMatrix();
	//////////////////////////////////////////////////////////////////////////////////
	
	//////////////////////shadows
	glPushMatrix();
	DrawShadowMatrixScene();
	light_.Render();
	//
	//for(int i = 0; i < 50; i++)
	//{
	//	for (int j = 0; j < 50; j++)
	//	{
	//		glPushMatrix();
	//		glTranslatef(i,0,j);
	//		floor_.Render();
	//		glPopMatrix();
	//	}
	//}
	////////////////////////////////////////////////////////////////////////////
	//temp.SetMaterialByTemplate(GOLD, WHITE);
	//temp.BindMaterial();

	//GLuint text2 = cloud_noise_.GetCloudNoiseTexture(*dt_);

	//glDisable(GL_LIGHTING);
	//glPushMatrix();
	//glBindTexture(GL_TEXTURE_2D, text);
	//glTranslatef(5, 5, 0);
	//glRotatef(-20, 0, 1, 0);
	//glScalef(5, 5, 5);
	//disc_.Draw();
	//glPopMatrix();
	//glEnable(GL_LIGHTING);

	
	/////custom shapes

	

	
	glPopMatrix();
	glPushMatrix();
	glTranslatef(4,0,0);
	gluSphere(gluNewQuadric(),2,20,20);
	glPopMatrix();
	/*glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


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
	glDisable(GL_BLEND);*/
	//Render HUD last

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
	glBegin(GL_QUADS);
	glNormal3f(0.0, 1.0, 0.0);
	glVertex3f(-5.0, -1.0, -5.0);
	glVertex3f(-5.0, -1.0, 5.0);
	glVertex3f(5.0, -1.0, 5.0);
	glVertex3f(5.0, -1.0, -5.0);
	glEnd();

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
