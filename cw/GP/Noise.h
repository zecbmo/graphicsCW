#ifndef NOISE_H_
#define NOISE_H_

#define NOISE_DEPTH 64
#define NOISE_WIDTH 256
#define NOISE_HEIGHT 192

#include <cstdlib>
#include <windows.h>
#include <stdio.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include "BaseColour.h"


//reference http://lodev.org/cgtutor/randomnoise.html
//converted to opengl textures 
//perlin noise math is essentially the same, however I have created the functions to 
//convert this to an opengl texture and animate it 

class Noise
{
public:
	Noise() { GenerateNoise(); anim_counter_ = 0; speed_ = 2; };
	~Noise() {};

	void GenerateNoise();
	GLuint GetCloudNoiseTexture(float dt);

private:
	
	float SmoothNoise(float x, float y, float z);
	float Turbulance(float x, float y, float z, float size);
	float noise_[NOISE_DEPTH][NOISE_HEIGHT][NOISE_WIDTH];
	Colour_RGBA colour_;
	float anim_counter_;
	float speed_;
	
};




#endif
