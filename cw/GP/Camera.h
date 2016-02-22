#pragma once
#include "Vector3.h"
#include <cmath>
class Camera
{
public:
	Camera();
	~Camera() {};

	void cameraUpdate();
	void changed();
	inline Vector3 getLookAtVec() { return position+forwardVec; };
	inline Vector3 getForwardVec() { return forwardVec; };
	inline Vector3 getUpVec() { return upVec; };
	inline Vector3 getPosition() { return position; };

	Vector3 getRightVec();
	Vector3 getRightVecDT(float speed, float dt);
	Vector3 getForwardVecDT(float speed, float dt);
	inline void setPosition(Vector3 newPos) { position = newPos; };
	inline void setRotation(float x, float y, float z) { pitch = x; yaw = y; roll = z; };
	inline void setPitch(float newPitch) { pitch = newPitch; };
	inline void setYaw(float newYaw) { yaw = newYaw; };
	inline void setRoll(float newRoll) { roll = newRoll; };
	inline float getPitch() { return pitch;	};
	inline float getYaw() { return yaw; };
	inline float getRoll() { return roll; };

private:
	Vector3 position;
	Vector3 prevPosition;
	float pitch, prevPitch, //rotation arround x-axis
		  yaw, prevYaw,		//y-axis
		  roll, prevRoll;	//z-axis
	Vector3 forwardVec;
	Vector3 lookAtVec;
	Vector3 upVec;
	Vector3 rightVec;

};

