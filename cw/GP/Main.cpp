//3D Framework main

// Includes
#include <windows.h>
#include <stdio.h>
#include "Input.h"
#include "Scene3D.h"
#include "Timer.h"
#include <gl/gl.h>
#include <gl/glu.h>
#include "SceneManager.h"


void SetVSync(bool sync); //obtained from Stewart McCready CGT


// Globals
HWND hwnd;
TestScene scene;
Timer timer;
Input input;

//Prototypes
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void RegisterMyWindow(HINSTANCE);
BOOL InitialiseMyWindow(HINSTANCE, int);
int WINAPI WinMain(HINSTANCE, HINSTANCE, PSTR, int);

// Defines the window
void RegisterMyWindow(HINSTANCE hInstance)
{
	WNDCLASSEX  wcex;

	wcex.cbSize = sizeof (wcex);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = 0;
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = "FirstWindowClass";
	wcex.hIconSm = 0;

	RegisterClassEx(&wcex);
}

// Attempts to create the window and display it
BOOL InitialiseMyWindow(HINSTANCE hInstance, int nCmdShow)
{
	hwnd = CreateWindow("FirstWindowClass",
		"Does it even matter what this is called?",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL,
		NULL,
		hInstance,
		NULL);
	if (!hwnd)
	{
		return FALSE;
	}

	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);
	return TRUE;

}

// Entry point. The program start here
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int nCmdShow)
{
	MSG         msg;
	RegisterMyWindow(hInstance);

	if (!InitialiseMyWindow(hInstance, nCmdShow))
		return FALSE;
	timer.Initialize();
	float* dt = timer.GetTimePointer();
	scene.Init(&hwnd, &input, dt);
	
	SetVSync(false);
	while (TRUE)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
				break;
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		else
		{
			// update delta time
			timer.Frame();
			// Update and render scene
			scene.Update();
		}

		if (input.IsKeyDown(VK_ESCAPE))
		{
			break;
		}
	}

	return msg.wParam;
}

// handles window messages				
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{

	switch (message)
	{
		case WM_CREATE:
			break;

		case WM_SIZE:
			scene.Resize();
			break;

		case WM_KEYDOWN:
			input.SetKeyDown(wParam);
			break;

		case WM_KEYUP:
			input.SetKeyUp(wParam);
			break;

		case WM_MOUSEMOVE:
			input.SetMouseX(LOWORD(lParam));
			input.SetMouseY(HIWORD(lParam));
			break;

		case WM_DESTROY:
			PostQuitMessage(0);
			break;
	}

	return DefWindowProc(hwnd, message, wParam, lParam);

}

void SetVSync(bool sync)  //obtained from Stewart McCready CGT
{
	// Function pointer for the wgl extention function we need to enable/disable
	// vsync
	typedef BOOL(APIENTRY *PFNWGLSWAPINTERVALPROC)(int);
	PFNWGLSWAPINTERVALPROC wglSwapIntervalEXT = 0;

	const char *extensions = (char*)glGetString(GL_EXTENSIONS);

	wglSwapIntervalEXT = (PFNWGLSWAPINTERVALPROC)wglGetProcAddress("wglSwapIntervalEXT");

	if (wglSwapIntervalEXT)
		wglSwapIntervalEXT(sync);

}