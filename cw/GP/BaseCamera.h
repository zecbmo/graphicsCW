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

class BaseCamera
{
public:
	BaseCamera();
	virtual ~BaseCamera() {};

	virtual void Init(Input* input);
	virtual void Update();
	virtual void Render();

	inline void SetPosition(Vector3 position) { position_ = position; };
	bool CameraChanged();

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

};


#endif

