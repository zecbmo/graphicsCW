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
    hdc = GetDC(*hwnd_);//  sets  global HDC

    if (!CreatePixelFormat(hdc))//  sets  pixel format
        PostQuitMessage (0);

    hrc = wglCreateContext(hdc);	//  creates  rendering context from  hdc
    wglMakeCurrent(hdc, hrc);		//	Use this HRC.

	ResizeGLWindow(width, height);	// Setup the Screen
}



void Scene3D::Init(HWND* wnd, Input* in, float* dt)
{
	InitHelper(wnd, in, dt);
	scene_to_load_ = BASE_SCENE;
	//Individual inits will go here
	//Init, Update and Render left here and allows for quick copy and paste to create new scenes
}

void Scene3D::Update()
{
	if (input_->IsKeyDown('8'))
	{
		scene_to_load_ = TESTING_SCENE;
	}
	//Update Everything here	
	Render();
}

void Scene3D::Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);// Clear The Screen And The Depth Buffer
	glLoadIdentity();// load Identity Matrix

	//Empty but left to remind of details of what is needed

	SwapBuffers(hdc);// Swap the frame buffers.
}		

void Scene3D::Resize()
{
	if(hwnd_ == NULL)
		return;

	GetClientRect(*hwnd_, &screenRect);
	ResizeGLWindow(screenRect.right, screenRect.bottom);	
}
void Scene3D::InitHelper(HWND* wnd, Input* in, float* dt)
{
	hwnd_ = wnd;
	input_ = in;
	dt_ = dt;
	GetClientRect(*hwnd_, &screenRect);	//get rect into our handy global rect
	InitializeOpenGL(screenRect.right, screenRect.bottom); // initialise openGL

	const GLubyte *str;
	int glPolyOffExtAvailable;

	str = glGetString(GL_EXTENSIONS);
	glPolyOffExtAvailable = (strstr((const char *)str, "WGL_EXT_swap_control") != NULL);

	//wglSwapIntervalEXT(0);

	//OpenGL settings
	glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
	glClearColor(0.0f, 0.0f, 0.2f, 1.0f);				// Black Background *no it isnt
	glClearDepth(1.0f);									// Depth Buffer Setup
	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
	glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations

	is_loaded_ = true;
}