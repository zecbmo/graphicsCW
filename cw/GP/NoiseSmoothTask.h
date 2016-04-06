#pragma once
#include "Task.h"
#include "Noise.h"

class NoiseSmoothtask : public Task
{
public:
	NoiseSmoothtask(float x, float y, float z, float size, float* value,  Noise* temp) : x_(x), y_(y), z_(z), size_(size),value_(value), noise_class_(temp) { };
	void Run();
private:
	Noise* noise_class_;
	float* value_;	
	float x_, y_, z_, size_;
};