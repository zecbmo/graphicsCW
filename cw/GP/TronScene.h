#pragma once

#include "Scene3D.h"
#include "Floor.h"
#include "TronWall.h"
#include "TronWall2.h"
#include "TronLight.h"
#include "TronDiscArena.h"

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
	void DrawWall();
	void DrawStartingRoom();


	CameraManager camera_manager_;
	Light light_;

	SkyBox sky_box_;

	Floor floor_;
	Floor corridor_;
	
	TronWall wall_;
	TronWall2 wall_two_;
	TronLight light_base_;
	TronDiscArena arena_;

	float uv_speed_; //for moving the skybox texture


};

