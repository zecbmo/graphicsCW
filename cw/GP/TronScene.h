#pragma once

#include "Scene3D.h"
#include "Floor.h"

class TronScene : public Scene3D
{
public:
	TronScene() {};
	~TronScene() {};

	void Init(HWND* hwnd, Input* in, float *dt);
	void Update();
	void Render();	// render scene

private:
	void DrawCorridor();
	void DrawFloors();


	CameraManager camera_manager_;
	Light light_;

	SkyBox sky_box_;

	Floor floor_;
	Floor corridor_;




};

