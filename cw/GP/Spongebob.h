#pragma once

#include "Scene3D.h"
#include "Noise.h"



class SpongebobScene : public Scene3D
{
public:
	SpongebobScene();
	~SpongebobScene();

	void Init(HWND* hwnd, Input* in, float *dt, HDC	hdc, HGLRC hrc, HGLRC hrc2);
	void ThreadFucntion(HDC	hdc, HGLRC hrc, HGLRC hrc2);
	void Update();
	void Render();	// render scene


private:
	CameraManager camera_manager_;
	Light light_;
	SkyBox sky_box_;

	
	Sphere beach_one_;
	Sphere beach_two_;
	Sphere beach_three_;


	Floor floor_;
	
	Model patrick_;
	Model spongebob_;
	Model pineapple_;
	Model gary_;
	Model palm_;





	//void DrawSpongeBobScene();
	
};

