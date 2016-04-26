#include "SceneManager.h"

Farm farm; //declare farm here as it is first class that uses it
std::atomic<bool> scene_loaded = false;
SceneManager::SceneManager()
{
	
}

SceneManager::~SceneManager()
{
	CleanUp();


}
void SceneManager::Init(HWND* hwnd, Input* input, float* dt)
{
	hwnd_ = hwnd;
	input_ = input;
	dt_ = dt;


	GetClientRect(*hwnd_, &screen_rect_);	//get rect into our handy global rect
	InitializeOpenGL(screen_rect_.right, screen_rect_.bottom); // initialise openGL

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

	current_scene_ = new MenuScene;
	current_scene_->Init(hwnd_, input_, dt_, hdc, hrc, hrc2);
	current_scene_type_ = LOADING_SCENE; //set to loading scene to init threads
	loading_scene_ = new LoadingScene;
	loading_scene_->Init(hwnd_, input_, dt_, hdc, hrc, hrc2);
	loading_ = false;
}
void SceneManager::InitializeOpenGL(int width, int height)
{
	hdc = GetDC(*hwnd_);//  sets  global HDC

	if (!CreatePixelFormat(hdc))//  sets  pixel format
		PostQuitMessage(0);

	hrc = wglCreateContext(hdc);	//  creates  rendering context from  hdc
	wglMakeCurrent(hdc, hrc);
	hrc2 = wglCreateContext(hdc);
	bool error = wglShareLists(hrc, hrc2);
	if (error == FALSE)
	{
		DWORD errorCode = GetLastError();
		LPVOID lpMsgBuf;
		FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
			NULL, errorCode, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR)&lpMsgBuf, 0, NULL);
		MessageBox(NULL, (LPCTSTR)lpMsgBuf, "Error", MB_OK | MB_ICONINFORMATION);
		LocalFree(lpMsgBuf);
		//Destroy the GL context and just use 1 GL context
		wglDeleteContext(hrc2);
	}

	//	Use this HRC.

	//ResizeGLWindow(width, height);	// Setup the Screen
}
bool SceneManager::CreatePixelFormat(HDC hdc)
{
	PIXELFORMATDESCRIPTOR pfd = { 0 };
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
	if ((pixelformat = ChoosePixelFormat(hdc, &pfd)) == false)
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
void SceneManager::Update()
{
	if (current_scene_->GetSceneToLoad() != current_scene_type_)
	{
		LoadScene();
	}
	//wglMakeCurrent(hdc, hrc);
	if (loading_ && scene_loaded)
	{
		
		current_scene_ = scene_to_load_;
		scene_to_load_ = NULL;
		farm.EndTasks();
		current_scene_->Init(hwnd_, input_, dt_, hdc, hrc, hrc2);
		current_scene_type_ = current_scene_->GetSceneToLoad();		
		loading_ = false; //local conrtoller
		scene_loaded = false; //global conrtoller
	}
	
	current_scene_->Update();
	

	

	
}
void SceneManager::LoadScene()
{
	scene_to_load_type_ = current_scene_->GetSceneToLoad();
	current_scene_type_ = LOADING_SCENE;
	delete current_scene_;
	switch (scene_to_load_type_)
	{
	case TESTING_SCENE:
		scene_to_load_ = new TestScene;
		break;
	case OPTIONS_SCENE: 
		scene_to_load_ = new MenuScene;
		break;
	case LEVEL_SCENE:
		break;
	case BASE_SCENE:
		scene_to_load_ = new Scene3D;
		break;
	case EARTH_SCENE:
		scene_to_load_ = new EarthScene;
		break;
	case TRON_SCENE: 
		scene_to_load_ = new TronScene;
		break;
	case ROBOT_ARM:
		scene_to_load_ = new RobotScene;
		break;
	case SPONGEBOB:
		scene_to_load_ = new SpongebobScene;
		break;
	default:
		break;
	}

	current_scene_ = loading_scene_;
	

	//add the loading 
	farm.AddTask(new LoadSceneTask(hdc, hrc, hrc2, scene_to_load_));
	//add update task to display loading screen
	//farm.AddTask(new DisplayLoadingScreen(current_scene_));
	farm.StartTasks();
	loading_ = true;
	
	
}
void SceneManager::CleanUp()
{
	delete loading_scene_;
	loading_scene_ = NULL;

	delete current_scene_;
	current_scene_ = NULL;
}
void SceneManager::Resize()
{
	current_scene_->Resize();

}

