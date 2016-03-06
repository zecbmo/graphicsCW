#include "RotatingCamera.h"

void RotatingCamera::Update()
{
	if ((end_pointer_ == NULL || start_pointer_ == NULL) && type_ == ANIMATED)
	{
		error::StringError(tag_, ": Rotating Camera, Start/End point not set");
	}

	switch (type_)
	{
	case ANIMATED:
		Animate();
		break;
	case ROTATE_TO_TARGET:
		RotateToTarget();
		break;
	default: error::StringError(tag_, ": Rotating Camerea, Animation Type not Set." );
		break;
	}

}
void RotatingCamera::SetStartPoint(Vector3 start_point)
{
	waiting = false; //as this function needs to be set to work other default values can be set here(make shift init)
	time_passed_ = 0;
	start_look_at_ = start_point; 
	start_pointer_ = &start_look_at_;
}
void RotatingCamera::SetEndPoint(Vector3 end_point)
{
	end_look_at_ = end_point;
	end_pointer_ = &end_look_at_;
}
void RotatingCamera::Animate()
{	
	if (!waiting)
	{
		float time_percent = time_passed_ / rotation_time_;
		look_at_vec_ = Lerp(time_percent, *start_pointer_, *end_pointer_);
		time_passed_ += *dt_;
		if (time_passed_ > rotation_time_)
		{
			waiting = true;
			time_passed_ = 0;
		}
	}
	else if (waiting)
	{
		time_passed_ += *dt_;
		if (time_passed_ > delay_)
		{
			Vector3* temp = start_pointer_;
			start_pointer_ = end_pointer_;
			end_pointer_ = temp;
			waiting = false;
			time_passed_ = 0;

		}
	}


}
void  RotatingCamera::RotateToTarget()
{
	look_at_vec_ = *target_;
}
Vector3 RotatingCamera::Lerp(float percent, Vector3& v1, Vector3& v2)
{
	Vector3 temp;
	temp.SetX((1 - percent) * v1.GetX() + percent * v2.GetX());
	temp.SetY((1 - percent) * v1.GetY() + percent * v2.GetY());
	temp.SetZ((1 - percent) * v1.GetZ() + percent * v2.GetZ());

	return temp;

}