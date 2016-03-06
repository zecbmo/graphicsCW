#include "Camera.h"

Camera::Camera()
{
	position_ = Vector3(0, 0, 10); 
	look_at_vec_ = Vector3(0, 0, 0);
	up_vec_ = Vector3(0, 1, 0);
	pitch_ = 0;
	yaw_ = 0;
	roll_ = 0;
	
}
void Camera::Init(Input* input, float* dt, RECT* screen_rect, HWND* hwnd,  std::string tag) //redefine this in child class and add pointers to objects which the class may need access to
{
	input_ = input;
	tag_ = tag;
	dt_ = dt;
	screen_rect_ = screen_rect;
	hwnd_ = hwnd;

}
void Camera::Render()
{
	gluLookAt(	position_.GetX(), position_.GetY(), position_.GetZ(),
				look_at_vec_.GetX(), look_at_vec_.GetY(), look_at_vec_.GetZ(),
				up_vec_.GetX(), up_vec_.GetY(), up_vec_.GetZ());
}
bool Camera::CameraChanged()
{
	if (!position_.Equals(prev_position_) || pitch_ != prev_pitch_ || yaw_ != prev_yaw_ || roll_ != prev_roll_)
	{
		return true;
	}

	return false;
}
void Camera::UpdatePosition()
{
	if (CameraChanged())
	{
		float cosR, cosP, cosY;	//temp values for sin/cos from 
		float sinR, sinP, sinY;

		// Roll, Pitch and Yall are variables stored by the camera
		// handle rotation
		// Only want to calculate these values once. 
		// For speeds sake. 
		cosY = cosf(yaw_*3.1415 / 180);
		cosP = cosf(pitch_*3.1415 / 180);
		cosR = cosf(roll_*3.1415 / 180);
		sinY = sinf(yaw_*3.1415 / 180);
		sinP = sinf(pitch_*3.1415 / 180);
		sinR = sinf(roll_*3.1415 / 180);

		forward_vec_.Set(sinY*cosP,
			sinP,
			cosP* -cosY);

		up_vec_.Set(-cosY * sinR - sinY * sinP * cosR,
			cosP * cosR,
			-sinY * sinR - sinP * cosR * -cosY);


		// Side Vector (right)
		// this is a cross product between the forward and up vector. 
		// If you don’t need to calculate this,  don’t do it. 


		prev_position_ = position_;
		prev_pitch_ = pitch_;
		prev_yaw_ = yaw_;
		prev_roll_ = roll_;

		look_at_vec_ = position_ + forward_vec_;
	}
}