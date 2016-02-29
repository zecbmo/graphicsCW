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
#include "BaseCamera.h"
#include "TextRenderer.h"
#include <complex>
#include "Shapes.h"
#include "Model.h"
#include "Light.h"
#include "Materials.h"

#define COLOUR_DEPTH 16	//Colour depth
/*
•	The scene must show lighting from at least 1 light source.Preferably multiple lights or different types, colours and some animated.
•	The scene must show use of texturing.Additionally demonstrating animated textures or advance use of texturing coordinates.
•	A working camera.The user must be able to manipulate the view through using the mouse and keyboard to control the camera.Additionally, 
	you should provide multiple cameras each with a different focus such as limited controls, fixed views, procedurally controlled views or different camera types.
•	A clear example of using the matrix stack for Hierarchical modelling and animation through hierarchical means.
•	Use of transparency effects / Alpha blending
•	Use of display lists and vertex arrays
•	Models loaded in from an external file
•	Examples of Procedurally generated shapes
•	User interaction(controlling objects in the scene other than the camera)
•	A wireframe mode
•	Advance features such as shadows and use of the stencil buffer
•	The application should be carefully designed and constructed showing appropriate use of classes and well commented*/


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
	void InitHelper(HWND* wnd, Input* in);
	
	//vars
	HWND* hwnd;
	Input* input;
	RECT screenRect;
	HDC	hdc;
	HGLRC hrc;			//hardware RENDERING CONTEXT
	int s_wdith, s_height;
	Light light_;


	//Cameras 
	BaseCamera cam;
	BaseCamera cam1;
	BaseCamera cam2;
	std::vector<BaseCamera*> cameras_;
	BaseCamera* current_camera_view_;

};

#endif