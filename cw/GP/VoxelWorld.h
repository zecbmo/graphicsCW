#pragma once


#include "Scene3D.h"
#include "Noise.h"

class VoxelScene : public Scene3D
{
public:
	VoxelScene() {};
	~VoxelScene() {};

	void Init(HWND* hwnd, Input* in, float *dt);
	void Update();
	void Render();	// render scene

private:
	CameraManager camera_manager_;
	Light light_;
	Noise cloud_noise_;
	GLuint earth_texture_;
	SkyBox sky_box_;
	Shapes sphere_, sphere2_;

	float earth_speed_;
	float cloud_speed_;
	float earth_rot_;
	float cloud_rot_;

	Vector3 camera_target_;

	Material default_material_;
};

