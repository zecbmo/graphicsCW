#ifndef ROTATING_CAMERA_
#define ROTATING_CAMERA_

#include "Camera.h"

class RotatingCamera : public Camera
{
public:
	RotatingCamera() {};
	~RotatingCamera() {};

	void Update();
	//target based
	inline void SetRotatingType(RotatingCameraType type) { type_ = type; };
	inline void SetTarget(Vector3* target) { target_ = target; };

	//animation based
	void SetStartPoint(Vector3 start_point);
	void SetEndPoint(Vector3 end_point);
	inline void SetTimeDelay(float delay) { delay_ = delay; };
	inline void SetRotationTime(float time) { rotation_time_ = time; };

private:
	void Animate();
	void RotateToTarget();
	Vector3 Lerp(float percent, Vector3 &v1, Vector3 &v2);

	RotatingCameraType type_; //animated or looks at target
	
	//target based 
	Vector3* target_;
	bool x_lock_, y_lock_, z_lock_;	

	//animation based
	Vector3 start_look_at_;
	Vector3 end_look_at_;
	Vector3* start_pointer_; //pointers to the start and end position to allow for easy switching
	Vector3* end_pointer_;
	float delay_; //The pause between going back and forward between the start and end vectors
	float rotation_time_; //the time it takes for rotation to finish
	float time_passed_; //monitors how much time has passed since rotation started (helps calculate lerp %)
	bool waiting;
};




#endif
