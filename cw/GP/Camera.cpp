#include "Camera.h"

Camera::Camera()
{
	position.set(0, 2, 6); 
	pitch = 0;
	yaw = 0; 
	roll = 0;

}
void Camera::cameraUpdate()
{

	if (!position.equals(prevPosition) || pitch != prevPitch || yaw != prevYaw || roll != prevRoll)
	{
		float cosR, cosP, cosY;	//temp values for sin/cos from 
		float sinR, sinP, sinY;

		// Roll, Pitch and Yall are variables stored by the camera
		// handle rotation
		// Only want to calculate these values once. 
		// For speeds sake. 
		cosY = cosf(yaw*3.1415 / 180);
		cosP = cosf(pitch*3.1415 / 180);
		cosR = cosf(roll*3.1415 / 180);
		sinY = sinf(yaw*3.1415 / 180);
		sinP = sinf(pitch*3.1415 / 180);
		sinR = sinf(roll*3.1415 / 180);

		forwardVec.set(sinY*cosP,
			sinP,
			cosP* -cosY);

		upVec.set(-cosY * sinR - sinY * sinP * cosR,
			cosP * cosR,
			-sinY * sinR - sinP * cosR * -cosY);


		// Side Vector (right)
		// this is a cross product between the forward and up vector. 
		// If you don’t need to calculate this,  don’t do it. 


		prevPosition = position;
		prevPitch = pitch;
		prevYaw = yaw;
		prevRoll = roll;
	}
}
void Camera::changed()
{
	if (!position.equals(prevPosition) || pitch != prevPitch || yaw != prevYaw || roll != prevRoll )
	{

	}
}
Vector3 Camera::getRightVec()
{
	return forwardVec.cross(upVec);
}
Vector3 Camera::getForwardVecDT(float speed, float dt)
{
	Vector3 temp;
	temp.setX(forwardVec.getX()*dt* speed);
	temp.setY(forwardVec.getY()*dt* speed);
	temp.setZ(forwardVec.getZ()*dt* speed);

	return temp;
}
Vector3 Camera::getRightVecDT(float speed, float dt)
{

	rightVec = forwardVec.cross(upVec);

	Vector3 temp;
	temp.setX(rightVec.getX()*dt* speed);
	temp.setY(rightVec.getY()*dt* speed);
	temp.setZ(rightVec.getZ()*dt* speed);

	return temp;
}