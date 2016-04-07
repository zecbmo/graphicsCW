#pragma once
#include "Task.h"
#include "Noise.h"

class NoiseTextask : public Task
{
public:
	NoiseTextask(int y_pos, int amount,  Noise* temp) : y_pos_(y_pos), amount_(amount), noise_class_(temp){ };
	void Run();
private:
	Noise* noise_class_;
	int y_pos_;
	int amount_;
	
};