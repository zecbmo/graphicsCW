#pragma once

#include "Scene3D.h"
#include "Floor.h"
#include "TronWall.h"
#include "TronWall2.h"
#include "TronLight.h"
#include "TronDiscArena.h"
#include "Cylinder.h"
#include "plane.h"
#include "Box.h"
#include "TronRecogniser.h"

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
	void DrawWallPictures();
	void DrawBoxes();

	CameraManager camera_manager_;
	Light light_;

	SkyBox sky_box_;

	Floor floor_;
	Floor corridor_;
	
	TronWall wall_;
	TronWall2 wall_two_;
	TronLight light_base_;
	TronDiscArena arena_;

	Cone cone_;
	Cylinder light_beam_centres_;
	Cylinder light_beam_outers_;

	Box blue_box_;
	Box red_box_;

	TronRecogniser recogniser_;



	Plane wall_pannel_;
	Plane wall_display_;
	Plane wall_display_2_;
	float uv_speed_; //for moving the skybox texture


};

