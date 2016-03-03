#include "Scene3D.h"
#include <math.h>
#include <iostream>
#include "include\SOIL.h"




bool Scene3D::CreatePixelFormat(HDC hdc) 
{ 
    PIXELFORMATDESCRIPTOR pfd = {0}; 
    int pixelformat; 
	
    pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);	// Set the size of the structure
    pfd.nVersion = 1;							// Always set this to 1
	// Pass in the appropriate OpenGL flags
	pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER; 
    pfd.dwLayerMask = PFD_MAIN_PLANE;			// standard mask (this is ignored anyway)
    pfd.iPixelType = PFD_TYPE_RGBA;				// RGB and Alpha pixel type
    pfd.cColorBits = COLOUR_DEPTH;				// Here we use our #define for the color bits
    pfd.cDepthBits = COLOUR_DEPTH;				// Ignored for RBA
    pfd.cAccumBits = 0;							// nothing for accumulation
    pfd.cStencilBits = 0;						// nothing for stencil
 
	//Gets a best match on the pixel format as passed in from device
    if ( (pixelformat = ChoosePixelFormat(hdc, &pfd)) == false ) 
    { 
        MessageBox(NULL, "ChoosePixelFormat failed", "Error", MB_OK); 
        return false; 
    } 
 
	//sets the pixel format if its ok. 
    if (SetPixelFormat(hdc, pixelformat, &pfd) == false) 
    { 
        MessageBox(NULL, "SetPixelFormat failed", "Error", MB_OK); 
        return false; 
    } 
 
    return true;
}

void Scene3D::ResizeGLWindow(int width, int height)// Initialize The GL Window
{
	if (height==0)// Prevent A Divide By Zero error
	{
		height=1;// Make the Height Equal One
	}

	glViewport(0,0,width,height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	//calculate aspect ratio
	gluPerspective(45.0f,(GLfloat)width/(GLfloat)height, 1 ,150.0f);

	glMatrixMode(GL_MODELVIEW);// Select The Modelview Matrix
	glLoadIdentity();// Reset The Modelview Matrix
}

void Scene3D::InitializeOpenGL(int width, int height) 
{  
    hdc = GetDC(*hwnd);//  sets  global HDC

    if (!CreatePixelFormat(hdc))//  sets  pixel format
        PostQuitMessage (0);

    hrc = wglCreateContext(hdc);	//  creates  rendering context from  hdc
    wglMakeCurrent(hdc, hrc);		//	Use this HRC.

	ResizeGLWindow(width, height);	// Setup the Screen
}



void Scene3D::Init(HWND* wnd, Input* in, float* dt)
{
	InitHelper(wnd, in);


	//////// Lighting
	glEnable(GL_LIGHTING);
	light_.Init(GL_LIGHT0, DIRECTIONAL_LIGHT);
	//light_.SetColourByTemplate(BLUE);
	light_.SetPosition(Vector3(-2.0f, 0.0f, 0.0f));
	light_.SetAllValues(1,1,1,1);
	light_.ResetAmbientToZero();
	/////// Materials 
	//glEnable(GL_COLOR_MATERIAL);

	/////// Textures 


	//cameras
	
	camera_manager_.Init(input, dt, &screenRect, hwnd );

	camera_manager_.CreateCamera(FIXED_POSITION, "fixed one");
	camera_manager_.CreateCamera(FIXED_POSITION, "fixed two");
	camera_manager_.CreateCamera(FIRST_PERSON, "floating one");
	camera_manager_.ChangeCamera("fixed one");
	camera_manager_.CurrentCamera()->SetPosition(Vector3(0, 0, -10));
	camera_manager_.GetCamera("floating one")->SetPosition(Vector3(10, 0, 10));
	camera_manager_.GetCamera("floating one")->SetSensitivity(10,10);

	camera_manager_.GetCamera("floating one")->SetAllSpeeds(10,10,10,10);






	


	int thisnUmber = 0;
	
	//camera_manager_.GetCamera("floating one")->SetSensitivity(5);
}

void Scene3D::Update(float dt)
{
	camera_manager_.Update();
	
	// Do important update here
	if (input->IsKeyDown('1'))
	{
		camera_manager_.ChangeCamera("fixed two");
		camera_manager_.GetCamera("fixed one")->SetPosition(Vector3(0,0, -40));
	}
	if (input->IsKeyDown('2'))
	{
		camera_manager_.ChangeCamera("fixed one");
	}
	else
	{
		camera_manager_.ChangeCamera("floating one");
	}
	
	

	
	
	Render();
}

void Scene3D::Render()
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
	temp.SetColour(Colour_RGBA(1,0,1,1));
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

void Scene3D::Resize()
{
	if(hwnd == NULL)
		return;

	GetClientRect(*hwnd, &screenRect);	
	ResizeGLWindow(screenRect.right, screenRect.bottom);	
}
void Scene3D::InitHelper(HWND* wnd, Input* in)
{
	hwnd = wnd;
	input = in;

	GetClientRect(*hwnd, &screenRect);	//get rect into our handy global rect
	InitializeOpenGL(screenRect.right, screenRect.bottom); // initialise openGL

	const GLubyte *str;
	int glPolyOffExtAvailable;

	str = glGetString(GL_EXTENSIONS);
	glPolyOffExtAvailable = (strstr((const char *)str, "WGL_EXT_swap_control") != NULL);

	//wglSwapIntervalEXT(0);

	//OpenGL settings
	glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
	glClearColor(0.0f, 0.0f, 0.7f, 1.0f);				// Black Background *no it isnt
	glClearDepth(1.0f);									// Depth Buffer Setup
	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
	glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations
}