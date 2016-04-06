#include "NoiseSmoothTask.h"

void NoiseSmoothtask::Run()
{
	noise_class_->ThreadSmoothNoise(x_, y_, z_, size_, value_);

}
