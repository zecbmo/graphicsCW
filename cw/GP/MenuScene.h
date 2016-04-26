#pragma once
#include "Scene3D.h"
#include "Noise.h"



class MenuScene : public Scene3D
{
public:
	MenuScene();
	~MenuScene();

	void Init(HWND* hwnd, Input* in, float *dt, HDC	hdc, HGLRC hrc, HGLRC hrc2);
	void Update();
	void Render();	// render scene
	void ThreadFucntion(HDC	hdc, HGLRC hrc, HGLRC hrc2);


private:
	CameraManager camera_manager_;
	Plane loading_screen_;


};
