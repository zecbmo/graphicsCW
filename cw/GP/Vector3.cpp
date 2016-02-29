#include "Vector3.h"
#include <cmath>
Vector3::Vector3(float x, float y, float z){
    this->x = x;
    this->y = y;
    this->z = z;
}
  
Vector3 Vector3::Copy(){
        Vector3 copy(
                this->x,
                this->y,     
                this->z);
        return copy;           
}
 
bool Vector3::Equals(const Vector3& v2, float epsilon){
        return ((abs(this->x - v2.x) < epsilon) &&
                    (abs(this->y - v2.y) < epsilon) &&
                        (abs(this->z - v2.z) < epsilon));      
}

bool Vector3::Equals(const Vector3& v2)
{
	return Equals(v2, 0.00001f);
}
 
 
float Vector3::Length(){
        return sqrt(this->LengthSquared());
}
 
float Vector3::LengthSquared(){
        return (
                this->x*this->x +
                this->y*this->y +
                this->z*this->z
                );
}
 
void Vector3::Normalise(){
    float mag = this->Length();
    if(mag){
            float multiplier = 1.0f/mag;
            this->x *= multiplier;
            this->y *= multiplier;
            this->z *= multiplier;
    }
}
 
Vector3 Vector3::Cross(const Vector3& v2){
        Vector3 cross(
                (this->y * v2.z - this->z * v2.y),
                (this->z * v2.x - this->x * v2.z),
                (this->x * v2.y - this->y * v2.x)
        );
        return cross;
}
 
void Vector3::Subtract(const Vector3& v1, float scale){
	this->x -= (v1.x*scale);
    this->y -= (v1.y*scale);
    this->z -= (v1.z*scale);         
}
 
void Vector3::Set(float x, float y, float z){
        this->x = x;
        this->y = y;
        this->z = z;
}
void Vector3::Set(Vector3 position)
{
	this->x = position.GetX();
	this->y = position.GetY();
	this->z = position.GetZ();
}

void Vector3::SetX(float x){
        this->x = x;
}
 
void Vector3::SetY(float y){
        this->y = y;
}
 
void Vector3::SetZ(float z){
        this->z = z;
}

float Vector3::GetX(){
       return this->x;
}
 
float Vector3::GetY(){
       return this->y;
}
 
float Vector3::GetZ(){
      return this->z;
}
 
float Vector3::Dot(const Vector3& v2){
        return (this->x*v2.x +
                this->y*v2.y +
                this->z*v2.z
                );
}
 
void Vector3::Scale(float scale){
	this->x*scale;
    this->y*scale;
    this->z*scale;
}
 
void Vector3::Add(const Vector3& v1, float scale){
	this->x += (v1.x*scale);
    this->y += (v1.y*scale);
    this->z += (v1.z*scale);
}
 
Vector3 Vector3::operator+(const Vector3& v2) {
	return Vector3(this->x + v2.x, this->y+v2.y, this->z+v2.z);
}
 
Vector3 Vector3::operator-(const Vector3& v2) {
    return Vector3(this->x - v2.x, this->y - v2.y, this->z - v2.z);
}
 
Vector3& Vector3::operator+=(const Vector3& v2) {
	this->x += v2.x;
	this->y += v2.y;
	this->z += v2.z;
	return *this;
}
 
Vector3& Vector3::operator-=(const Vector3& v2) {
	this->x -= v2.x;
	this->y -= v2.y;
	this->z -= v2.z;
	return *this;
}
