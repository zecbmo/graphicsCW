#ifndef _VECTOR3_H_
#define _VECTOR3_H_

#include <math.h>
 
class Vector3{

public:
    Vector3(float x = 0, float y = 0, float z = 0);
	
	Vector3 Copy(); 
    void Set(float x, float y, float z);
	void Set(Vector3 position);
    void SetX(float x);
    void SetY(float y);
    void SetZ(float z);

	float GetX();
	float GetY();
	float GetZ();
 
    void Add(const Vector3& v1, float scale=1.0);
    void Subtract(const Vector3& v1, float scale=1.0);
    void Scale(float scale);
 
    float Dot(const Vector3& v2);
    Vector3 Cross(const Vector3& v2);
 
    void Normalise();
    float Length();
    float LengthSquared();
 
    bool Equals(const Vector3& v2, float epsilon);
	bool Equals(const Vector3& v2);
 
    Vector3 operator+(const Vector3& v2);
    Vector3 operator-(const Vector3& v2);
 
    Vector3& operator+=(const Vector3& v2);
    Vector3& operator-=(const Vector3& v2);



private:
    float x;
	float y;
	float z;
};

#endif