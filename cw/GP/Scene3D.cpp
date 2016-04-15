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
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);				// Black Background *no it isnt
	glClearDepth(1.0f);									// Depth Buffer Setup
	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
	glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations
	wireframe_ = false;
	is_loaded_ = true;
	movement_speed_ = 1;
	debug_title_font_.Init("fonts/trekfont.png");
	debug_font_.Init("fonts/erasfont.png");
	object_tracker_ = NULL;
	movement_type_ = POSITION;
	
}

void Scene3D::SharedControls()
{

	if (input_->IsKeyDown('T'))
	{
		wireframe_ = !wireframe_;
		input_->SetKeyUp('T');
	}

	if (wireframe_)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	else
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	}

	if (object_tracker_ != NULL)
	{
		widget_.Update(object_tracker_->GetPosition()); 
	}
}

void Scene3D::GameObjectMover(GameObject &gameObject)
{
	object_tracker_ = &gameObject;
	switch (movement_type_)
	{
	case ROTATION:
		MoveRotation(gameObject);
		break;
	case POSITION:
		MovePosition(gameObject);
		break;
	case SCALE:
		MoveScale(gameObject);
		break;
	default:
		break;
	}

	if (input_->IsKeyDown('M'))
	{
		switch (movement_type_)
		{
		case ROTATION:
			movement_type_ = POSITION;
			break;
		case POSITION:
			movement_type_ = SCALE;
			break;
		case SCALE:
			movement_type_ = ROTATION;
			break;
		default:
			break;
		}
		input_->SetKeyUp('M');
	}
	if (input_->IsKeyDown(VK_ADD))
	{
		movement_speed_ += 5;
		input_->SetKeyUp(VK_ADD);

	}
	if (input_->IsKeyDown(VK_SUBTRACT))
	{
		movement_speed_ -= 5;
		input_->SetKeyUp(VK_SUBTRACT);

	}
	
	if (input_->IsKeyDown('X'))
	{
		rot_type_ = ROT_X;
		input_->SetKeyUp('X');

	}
	if (input_->IsKeyDown('Y'))
	{
		rot_type_ = ROT_Y;
		input_->SetKeyUp('Y');

	}
	if (input_->IsKeyDown('Z'))
	{
		rot_type_ = ROT_Z;
		input_->SetKeyUp('Z');

	}
	if (input_->IsKeyDown('C'))
	{
		rot_type_ = SCALE_ALL;
		input_->SetKeyUp('C');

	}



}

void Scene3D::MovePosition(GameObject & gameObject)
{
	float x = gameObject.GetPosition().GetX();
	float y = gameObject.GetPosition().GetY();
	float z = gameObject.GetPosition().GetZ();



	if (input_->IsKeyDown(VK_DOWN))
	{
		gameObject.SetPosition(Vector3(x - movement_speed_*(*dt_), y, z));
	}
	if (input_->IsKeyDown(VK_UP))
	{
		gameObject.SetPosition(Vector3(x + movement_speed_*(*dt_), y, z));

	}
	if (input_->IsKeyDown(VK_RIGHT))
	{
		gameObject.SetPosition(Vector3(x, y, z + movement_speed_*(*dt_)));
	}
	if (input_->IsKeyDown(VK_LEFT))
	{
		gameObject.SetPosition(Vector3(x, y, z - movement_speed_*(*dt_)));

	}
	if (input_->IsKeyDown('R'))
	{
		gameObject.SetPosition(Vector3(x, y + movement_speed_*(*dt_), z));

	}
	if (input_->IsKeyDown('F'))
	{
		gameObject.SetPosition(Vector3(x, y - movement_speed_*(*dt_), z));

	}
}

void Scene3D::MoveRotation(GameObject & gameObject)
{
	float x = gameObject.GetRotation().GetX();
	float y = gameObject.GetRotation().GetY();
	float z = gameObject.GetRotation().GetZ();

	float rot_speed = movement_speed_;

	if (input_->IsKeyDown('R'))
	{
		gameObject.SetRotation(0, 0, 0);
	}

	switch (rot_type_)
	{
	case ROT_X:
	{
		if (input_->IsKeyDown(VK_LEFT))
		{
			gameObject.SetRotation(x - rot_speed*(*dt_),y,z);
		}
		if (input_->IsKeyDown(VK_RIGHT))
		{
			gameObject.SetRotation(x + rot_speed*(*dt_), y, z);
		}
	}
		break;
	case ROT_Y:
	{
		if (input_->IsKeyDown(VK_LEFT))
		{
			gameObject.SetRotation(x, y - rot_speed*(*dt_), z);

		}
		if (input_->IsKeyDown(VK_RIGHT))
		{
			gameObject.SetRotation(x, y + rot_speed*(*dt_), z);

		}
	}
		break;
	case ROT_Z:
	{
		if (input_->IsKeyDown(VK_LEFT))
		{
			gameObject.SetRotation(x, y, z - rot_speed*(*dt_));

		}
		if (input_->IsKeyDown(VK_RIGHT))
		{
			gameObject.SetRotation(x, y, z + rot_speed*(*dt_));

		}
	}
		break;
	default:
		break;
	}


}

void Scene3D::MoveScale(GameObject & gameObject)
{
	float x = gameObject.GetScale().GetX();
	float y = gameObject.GetScale().GetY();
	float z = gameObject.GetScale().GetZ();

	float scale_speed = movement_speed_;

	if (input_->IsKeyDown('R'))
	{
		gameObject.SetScale(1, 1, 1);
	}

	switch (rot_type_)
	{
	case ROT_X:
	{
		if (input_->IsKeyDown(VK_LEFT))
		{
			gameObject.SetScale(x - scale_speed*(*dt_), y ,z);
		}
		if (input_->IsKeyDown(VK_RIGHT))
		{
			gameObject.SetScale(x + scale_speed*(*dt_), y,z);
		}
	}
	break;
	case ROT_Y:
	{
		if (input_->IsKeyDown(VK_LEFT))
		{
			gameObject.SetScale(x, y - scale_speed*(*dt_), z);
		}
		if (input_->IsKeyDown(VK_RIGHT))
		{
			gameObject.SetScale(x, y + scale_speed*(*dt_),z);
		}
	}
	break;
	case ROT_Z:
	{
		if (input_->IsKeyDown(VK_LEFT))
		{
			gameObject.SetScale(x, y, z - scale_speed*(*dt_));
		}
		if (input_->IsKeyDown(VK_RIGHT))
		{
			gameObject.SetScale(x, y, z + scale_speed*(*dt_));
		}
	}
	break;
	case SCALE_ALL:
	{
		if (input_->IsKeyDown(VK_LEFT))
		{
			gameObject.SetScale(x - scale_speed*(*dt_), y - scale_speed*(*dt_), z - scale_speed*(*dt_));
		}
		if (input_->IsKeyDown(VK_RIGHT))
		{
			gameObject.SetScale(x + scale_speed*(*dt_), y + scale_speed*(*dt_), z + scale_speed*(*dt_));
		}
	}
	break;
	default:
		break;
	}
	
}

void Scene3D::DisplayHUD(Camera* camera)
{
	//////////////////////////////////////switch to ortho
	glDisable(GL_LIGHTING);
	glDepthMask(GL_FALSE);  // disable writes to Z-Buffer
	glDisable(GL_DEPTH_TEST);  // disable depth-testing
	glMatrixMode(GL_PROJECTION);					// Select Projection
	glPushMatrix();							// Push The Matrix
	glLoadIdentity();						// Reset The Matrix
	glOrtho(0, screenRect.right, -screenRect.bottom, 0, -10, 10);				// Select Ortho Mode, 0,0 to start fropm the top left
	glMatrixMode(GL_MODELVIEW);					// Select Modelview Matrix
	glPushMatrix();							// Push The Matrix
	glLoadIdentity();
	
	/////////////////////////////////////  GUI drawing goes here
	
	
	glPushMatrix();
	GUIToScreenSize(0.9, 0.94);
	ShowFPS();
	glPopMatrix();

	glPushMatrix();
	GUIToScreenSize(0, 0.1);
	glScalef(1.2, 1.2, 0);
	debug_title_font_.DrawString(title_, 0, 0, 4, 4);
	glPopMatrix();


	glPushMatrix();

	

	if (object_tracker_ == NULL)
	{
		GUIToScreenSize(0.005, 0.94);
		debug_font_.DrawString("No object set for tracking", 0, 0, 4, 4);
	}
	else
	{
		glPushMatrix();
		GUIToScreenSize(0.005, 0.2);
		ShowMovementType();
		glPopMatrix();

		glPushMatrix();
		GUIToScreenSize(0.005, 0.75);
		ShowObjectStats();
		glPopMatrix();
			
	}


	glPopMatrix();


	


	///////////////////////////////////////// switch to projection


	glMatrixMode(GL_PROJECTION);					// Select Projection
	glPopMatrix();							// Pop The Matrix
	glMatrixMode(GL_MODELVIEW);					// Select Modelview
	glPopMatrix();

	widget_.Render();



	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);  // disable writes to Z-Buffer
	glEnable(GL_LIGHTING);
	
	
}
void Scene3D::ShowFPS()
{
	char buffer[255];
	frametimer_ += *dt_;
	framecounter_++;



	if (frametimer_ >= 1)
	{
		fps_ = framecounter_;
		frametimer_ = 0;
		framecounter_ = 0;
	}

	sprintf_s(buffer, "FPS: %d\n", fps_);
	debug_font_.DrawString(buffer, 0, 0, 4, 4);
}
void Scene3D::GUIToScreenSize(float x, float y) //x and y should be in range of 0 and 1
{
	float w = screenRect.right;
	float h = screenRect.bottom;
		
	x = x * w;
	y = y * h;

	float s = (w / h);
	s = s*4;
	glTranslatef(x , -y, 0);
	glScalef(s,s,0);
		
}
void Scene3D::ShowObjectStats()
{
	Vector3 pos = object_tracker_->GetPosition();
	float x = pos.GetX();
	float y = pos.GetY();
	float z = pos.GetZ();

	Vector3 rot = object_tracker_->GetRotation();
	float xr = rot.GetX();
	float yr = rot.GetY();
	float zr = rot.GetZ();

	Vector3 scale = object_tracker_->GetScale();
	float xs = scale.GetX();
	float ys = scale.GetY();
	float zs = scale.GetZ();


	char buffer[255];
	sprintf_s(buffer, "x: %.2f y: %.2f z: %.2f", x,y,z);
	debug_font_.DrawString("Object Position", 0, 0, 4, 4);
	glTranslatef(0, -3, 0);
	debug_font_.DrawString(buffer, 0, 0, 4, 4);
	glTranslatef(0, -3, 0);
	debug_font_.DrawString("Object Rotation", 0, 0, 4, 4);
	glTranslatef(0, -3, 0);
	sprintf_s(buffer, "x: %.2f y: %.2f z: %.2f", xr, yr, zr);
	debug_font_.DrawString(buffer, 0, 0, 4, 4);
	glTranslatef(0, -3, 0);
	debug_font_.DrawString("Object Scale", 0, 0, 4, 4);
	glTranslatef(0, -3, 0);
	sprintf_s(buffer, "x: %.2f y: %.2f z: %.2f", xs, ys, zs);
	debug_font_.DrawString(buffer, 0, 0, 4, 4);
}

void Scene3D::ShowMovementType()
{
	debug_font_.DrawString("Movement tool:", 0, 0, 4, 4);
	glTranslatef(0, -3, 0);
	debug_font_.DrawString("'M' to switch tool type.", 0, 0, 4, 4);
	glTranslatef(0, -3, 0);
	debug_font_.DrawString("+/- to change Speed.", 0, 0, 4, 4);
	glTranslatef(0, -3, 0);
	char buffer[255];
	sprintf_s(buffer, "Speed: %.2f", movement_speed_);
	debug_font_.DrawString(buffer, 0, 0, 4, 4);
	glTranslatef(0, -6, 0);

	switch (movement_type_)
	{
	case ROTATION:
	{
		switch (rot_type_)
		{
		case ROT_X:
		{
			debug_font_.DrawString("Rotation tool selected: x", 0, 0, 4, 4);
		}
			break;	
		case ROT_Y:
		{
			debug_font_.DrawString("Rotation tool selected: y", 0, 0, 4, 4);

		}
			break;
		case ROT_Z:
		{
			debug_font_.DrawString("Rotation tool selected: z", 0, 0, 4, 4);
		}
			break;
		case SCALE_ALL:
		{
			debug_font_.DrawString("All not available for Rotaion! Please select x,y,z", 0, 0, 4, 4);
		}
		break;
		default:
			break;
		}
		glTranslatef(0, -3, 0);
		debug_font_.DrawString("'X' 'Y' or 'Z' to switch rotation type", 0, 0, 4, 4);
	}
		break;
	case POSITION:
	{
		debug_font_.DrawString("Positioning tool selected", 0, 0, 4, 4);

	
	}
		break;
	case SCALE:
	{
		switch (rot_type_)
		{
		case ROT_X:
		{
			debug_font_.DrawString("Scale tool selected: x", 0, 0, 4, 4);
		}
		break;
		case ROT_Y:
		{
			debug_font_.DrawString("Scale tool selected: y", 0, 0, 4, 4);

		}
		break;
		case ROT_Z:
		{
			debug_font_.DrawString("Scale tool selected: z", 0, 0, 4, 4);
		}
		break;
		case SCALE_ALL:
		{
			debug_font_.DrawString("Scale tool selected: All", 0, 0, 4, 4);
		}
		break;
		default:
			break;
		}
		glTranslatef(0, -3, 0);
		debug_font_.DrawString("'X' 'Y' 'Z' 'C' to switch scale type", 0, 0, 4, 4);
	
	}
		break;
	default:
		break;
	}
}
