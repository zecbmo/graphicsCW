#ifndef BASE_CAMERA_
#define BASE_CAMERA_

#include <windows.h>
#include <stdio.h>
#include <mmsystem.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include "Vector3.h"
#include <cmath>
#include <iostream>
#include "ErrorSystem.h"
#include "Input.h"
#include <string>


class Camera
{
public:
	Camera();
	virtual ~Camera() {};

	//Shared Functions 
	void Init(Input* input, float* dt, RECT* screen_rect, HWND* hwnd, std::string tag);
	inline void SetPosition(Vector3 position) { position_ = position; };
	inline std::string GetTag() { return tag_; };
	bool CameraChanged();
	void UpdatePosition();
	void Render();
	
	//virtual functions created for specific camera classes, identified in base camera class as to access this from the camera manager (Camera*) 
	virtual void Update() {};

	//cameras that contain mouse control
	virtual void SetSensitivity(float x_sensitivity, float y_sensitivity) {};

	//cameras with keyboard control
	virtual void SetAllSpeeds(float forward_speed, float backward_speed, float strafe_speed, float vertical_speed) {};
	virtual void SetForwardSpeed(float speed) { };
	virtual void SetBackwardSpeed(float speed) {};
	virtual void SetStrafeSpeed(float speed) { };
	virtual void SetVerticalSpeed(float speed) {};


protected:
	Vector3 position_;
	Vector3 prev_position_;
	float pitch_, prev_pitch_, //rotation arround x-axis
		  yaw_, prev_yaw_,		//y-axis
		  roll_, prev_roll_;	//z-axis
	Vector3 forward_vec_;
	Vector3 look_at_vec_;
	Vector3 up_vec_;
	Vector3 right_vec_;
	

	Input* input_;
	float* dt_;
	RECT* screen_rect_;
	HWND* hwnd_;
	std::string tag_;


};


#endif

