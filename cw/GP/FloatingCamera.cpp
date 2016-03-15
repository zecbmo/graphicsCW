#include "FloatingCamera.h"

void FloatingCamera::Update()
{
	MouseControls();
	KeyboardControls();
	UpdatePosition();
	
}
void FloatingCamera::MouseControls()
{
	

	float cenX = screen_rect_->right / 2;
	float cenY = screen_rect_->bottom / 2;

	float diffx = input_->GetMouseX() - cenX;
	float diffy = input_->GetMouseY() - cenY;
	
	float deadzone = 1; //stops the camera moving on a 4k monitor when the mouse is still :D

	if (abs(diffx) > deadzone || abs(diffy) > deadzone)
	{
		yaw_ = yaw_ + diffx * (*dt_) * x_speed_;
		pitch_ = pitch_ - diffy * (*dt_) * y_speed_;
	}
	
	if (pitch_ > 80 || pitch_ < -80)
	{
		pitch_ = prev_pitch_;
	}
	POINT temp;
	temp.x = cenX;
	temp.y = cenY;
	ClientToScreen(*hwnd_, &temp);
	SetCursorPos(temp.x, temp.y);
	

	char buffer[255];
	sprintf_s(buffer, "Pitch: %.f\n", pitch_);
	OutputDebugString(buffer);

}
void FloatingCamera::KeyboardControls()
{
	bool temp = input_->IsKeyDown('W');

	if (input_->IsKeyDown('W'))
	{
		Vector3 temp;
		temp.SetX(forward_vec_.GetX() * (*dt_) * forward_speed_);
		temp.SetY(forward_vec_.GetY() * (*dt_) * forward_speed_);
		temp.SetZ(forward_vec_.GetZ() * (*dt_) * forward_speed_);

		position_ = position_ + temp;
	}
	if (input_->IsKeyDown('S'))
	{
		Vector3 temp;
		temp.SetX(forward_vec_.GetX() * (*dt_) * backward_speed_);
		temp.SetY(forward_vec_.GetY() * (*dt_) * backward_speed_);
		temp.SetZ(forward_vec_.GetZ() * (*dt_) * backward_speed_);

		position_ = position_ - temp;
	}
	if (input_->IsKeyDown('A'))
	{
		right_vec_ = forward_vec_.Cross(up_vec_);

		Vector3 temp;
		temp.SetX(right_vec_.GetX() * (*dt_) * strafe_speed_);
		temp.SetY(right_vec_.GetY() * (*dt_) * strafe_speed_);
		temp.SetZ(right_vec_.GetZ() * (*dt_) * strafe_speed_);

		position_ = position_ - temp;
	}
	if (input_->IsKeyDown('D'))
	{
		right_vec_ = forward_vec_.Cross(up_vec_);

		Vector3 temp;
		temp.SetX(right_vec_.GetX() * (*dt_) * strafe_speed_);
		temp.SetY(right_vec_.GetY() * (*dt_) * strafe_speed_);
		temp.SetZ(right_vec_.GetZ() * (*dt_) * strafe_speed_);

		position_ = position_ + temp;
	}
	if (input_->IsKeyDown('C'))
	{
	

		Vector3 temp;
		temp.SetX(up_vec_.GetX() * (*dt_) * vertical_speed_);
		temp.SetY(up_vec_.GetY() * (*dt_) * vertical_speed_);
		temp.SetZ(up_vec_.GetZ() * (*dt_) * vertical_speed_);

		position_ = position_ + temp;
	}
	if (input_->IsKeyDown('Z'))
	{


		Vector3 temp;
		temp.SetX(up_vec_.GetX() * (*dt_) * vertical_speed_);
		temp.SetY(up_vec_.GetY() * (*dt_) * vertical_speed_);
		temp.SetZ(up_vec_.GetZ() * (*dt_) * vertical_speed_);

		position_ = position_ - temp;
	}
	if (input_->IsKeyDown('E'))
	{


		Vector3 temp;
		temp.SetX(0);
		temp.SetY(1 * (*dt_) * vertical_speed_);
		temp.SetZ(0);

		position_ = position_ + temp;
	}
	if (input_->IsKeyDown('Q'))
	{


		Vector3 temp;
		temp.SetX(0);
		temp.SetY(1 * (*dt_) * vertical_speed_);
		temp.SetZ(0);

		position_ = position_ - temp;
	}

}
