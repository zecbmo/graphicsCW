#ifndef SCENE3D_H
#define SCENE3D_H

#include <windows.h>
#include <stdio.h>
#include <mmsystem.h>
#include <math.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include "Input.h"
#include "Vector3.h"
#include "Camera.h"
#include "TextRenderer.h"
#include <complex>
#include "Shapes.h"
#include "Model.h"

#define COLOUR_DEPTH 16	//Colour depth

using namespace shapes;

class Scene3D
{
public:
	void Init(HWND* hwnd, Input* in);	//initialse function
	void Update(float dt);
	void Render();	// render scene
	void Resize();

protected:
	bool CreatePixelFormat(HDC hdc);
	void ResizeGLWindow(int width, int height);	//width and height
	void InitializeOpenGL(int width, int height); // width and height
	
	//vars
	HWND* hwnd;
	Input* input;
	RECT screenRect;
	HDC	hdc;
	HGLRC hrc;			//hardware RENDERING CONTEXT
	int s_wdith, s_height;
	

};

#endif