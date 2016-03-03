#ifndef FLOATING_CAMERA_
#define FLOATING_CAMERA_
#include "Camera.h"

class FloatingCamera :public Camera
{
public:
	FloatingCamera() {};
	~FloatingCamera() {};

	void Update();

	inline void SetSensitivity(float x_sensitivity, float y_sensitivity) { x_speed_ = x_sensitivity; y_speed_ = y_sensitivity; };
	inline void SetAllSpeeds(float forward_speed, float backward_speed, float strafe_speed, float vertical_speed) { forward_speed_ = forward_speed; backward_speed_ = backward_speed; strafe_speed_ = strafe_speed; vertical_speed_ = vertical_speed;};
	inline void SetForwardSpeed(float speed) { forward_speed_ = speed; };
	inline void SetBackwardSpeed(float speed) { backward_speed_ = speed; };
	inline void SetStrafeSpeed(float speed) { strafe_speed_ = speed; };
	inline void SetVerticalSpeed(float speed) { vertical_speed_ = speed; };
	
private:
	void MouseControls();
	void KeyboardControls();

	float x_speed_; //used for sensitivity
	float y_speed_;
	float forward_speed_;
	float backward_speed_;
	float strafe_speed_;
	float vertical_speed_;
	
};




#endif

