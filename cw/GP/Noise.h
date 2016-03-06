#ifndef NOISE_H_
#define NOISE_H_

#define NOISE_DEPTH 64
#define NOISE_WIDTH 192
#define NOISE_HEIGHT 192

#include <cstdlib>
#include <windows.h>
#include <stdio.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include "BaseColour.h"


//reference http://lodev.org/cgtutor/randomnoise.html
//converted to opengl textures 

//RBG converters https://github.com/ratkins/RGBConverter/blob/master/RGBConverter.cpp



class Noise
{
public:
	Noise() { GenerateNoise(); };
	~Noise() {};

	void GenerateNoise();
	GLuint GetCloudNoiseTexture();

private:
	
	double SmoothNoise(double x, double y, double z);
	double Turbulance(double x, double y, double z, double size);
	Colour_RGBA HSLtoRGBA(double h, double s, double l);
	float HUEtoRGB(double p, double q, double t);
	double noise_[NOISE_DEPTH][NOISE_HEIGHT][NOISE_WIDTH];
	Colour_RGBA colour_;
	
};




#endif
