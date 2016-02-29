#include "BaseCamera.h"

BaseCamera::BaseCamera()
{
	position_ = Vector3(0, 0, 10); 
	look_at_vec_ = Vector3(0, 0, 0);
	up_vec_ = Vector3(0, 1, 0);
	pitch_ = 0;
	yaw_ = 0;
	roll_ = 0;

}
void BaseCamera::Init(Input* input) //redefine this in child class and add pointers to objects which the class may need access to
{
	input_ = input;
}
void BaseCamera::Update()
{
	char buffer[255];
	sprintf_s(buffer, "Updating Cameras\n");
	//std::string temp = "FPS: " + framecounter;
	//std::cout << "fps: " << framecounter << std::endl;
	OutputDebugString(buffer);
}
void BaseCamera::Render()
{
	gluLookAt(	position_.GetX(), position_.GetY(), position_.GetZ(),
				look_at_vec_.GetX(), look_at_vec_.GetY(), look_at_vec_.GetZ(),
				up_vec_.GetX(), up_vec_.GetY(), up_vec_.GetZ());
}
bool BaseCamera::CameraChanged()
{
	if (!position_.Equals(prev_position_) || pitch_ != prev_pitch_ || yaw_ != prev_yaw_ || roll_ != prev_roll_)
	{
		return true;
	}

	return false;
}