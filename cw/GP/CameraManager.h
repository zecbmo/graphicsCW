#ifndef CAMERA_MANAGER_
#define CAMERA_MANAGER_

#include <windows.h>
#include <stdio.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include <vector>
#include "Input.h"
#include "Camera.h"
#include "FloatingCamera.h"
#include "FPS_Camera.h"
#include <string>
#include "ErrorSystem.h"


enum CameraType {FIXED_POSITION, FLOATING, ROTATING, SCROLLING, MOVABLE, TRACKING, PUSHABLE, FIRST_PERSON};

class CameraManager
{
public:
	CameraManager();
	~CameraManager();

	void Init(Input* input, float* dt, RECT* screen_rect, HWND* hwnd);
	void CreateCamera(CameraType type, std::string tag);
	void DeleteCamera(std::string tag);
	Camera* CurrentCamera();
	Camera* GetCamera(std::string tag);
	void ChangeCamera(std::string tag);

	void Update();
	void Render();

	void CleanUp();

private:
	bool CheckTagExists(std::string tag);

	std::vector<Camera*> camera_list_;
	Camera* current_camera_;

	Input* input_;	
	float* dt_;
	RECT* screen_rect_;
	HWND* hwnd_;
};


#endif
