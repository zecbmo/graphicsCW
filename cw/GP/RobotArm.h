#pragma once

#pragma once

#include "Scene3D.h"
#include "Noise.h"

class RobotScene : public Scene3D
{
public:
	RobotScene() {};
	~RobotScene();

	void Init(HWND* hwnd, Input* in, float *dt, HDC	hdc, HGLRC hrc, HGLRC hrc2);
	void ThreadFucntion(HDC	hdc, HGLRC hrc, HGLRC hrc2);
	void Update();
	void Render();	// render scene

private:
	void createCubeFromPoint(float x, float y, float z);
	CameraManager camera_manager_;
	Light light_;

	float rotation;
	float rotation2;
	float speed;

	float mainBodyRotZ;
	float mainBodyRotY;
	float forArmRot;
	float handRotZ;
	float handRotY;
	float digitRot[3];

};

