#include "Noise.h"

void Noise::GenerateNoise()
{
	for (int z = 0; z < NOISE_DEPTH; z++)
	{
		for (int y = 0; y < NOISE_HEIGHT; y++)
		{
			for (int x = 0; x < NOISE_WIDTH; x++)
			{
				noise_[z][y][x] = (rand() % 32768) / 32768.0;
			}
		}
	}
	int blah = 0;
}

double Noise::SmoothNoise(double x, double y, double z)
{
	//get fractal
	double fract_x = x - int(x);
	double fract_y = y - int(y);
	double fract_z = z - int(z);

	//wrap arround
	int x1 = (int(x) + NOISE_WIDTH) % NOISE_WIDTH;
	int y1 = (int(y) + NOISE_HEIGHT) % NOISE_HEIGHT;
	int z1 = (int(z) + NOISE_DEPTH) % NOISE_DEPTH;

	//neighbour values
	int x2 = (x1 + NOISE_WIDTH - 1) % NOISE_WIDTH;
	int y2 = (y1 + NOISE_HEIGHT - 1) % NOISE_HEIGHT;
	int z2 = (z1 + NOISE_DEPTH - 1) % NOISE_DEPTH;

	//smooth with bi-linear interpolation (we learnt this in class)
	double value = 0.0f;

	value += fract_x * fract_y * fract_z * noise_[z1][y1][x1];
	value += fract_x * (1 - fract_y) * fract_z * noise_[z1][y2][x1];
	value += (1 - fract_x) * fract_y * fract_z * noise_[z1][y1][x2];
	value += (1 - fract_x) * (1 - fract_y) * fract_z * noise_[z1][y2][x2];

	value += fract_x * fract_y * (1 - fract_z) * noise_[z2][y1][x1];
	value += fract_x * (1 - fract_y) * (1 - fract_z) * noise_[z2][y2][x1];
	value += (1 - fract_x) * fract_y * (1 - fract_z) * noise_[z2][y1][x2];
	value += (1 - fract_x) * (1 - fract_y) * (1 - fract_z) * noise_[z2][y2][x2];

	return value;





}

double Noise::Turbulance(double x, double y, double z, double size)
{
	double value = 0.0f;
	double initial_size = size;
	double z2 = z;
	while (size >= 1)
	{
		value += SmoothNoise(x / size, y / size, z / size) * size;
		size /= 2.0;
	}

	return(128.0f * value / initial_size);

	return 0.0f;
}

GLuint Noise::GetCloudNoiseTexture(float dt)
{
	uint32_t image[NOISE_HEIGHT][NOISE_WIDTH]; //storage for the RGBA values of each pixel
		
	for (int y = 0; y < NOISE_HEIGHT; y++)
	{
		for (int x = 0; x < NOISE_WIDTH; x++)
		{
			//this code is based off of Hue, Saturationa and light
			//I have modified it so it is based off of a pure white texture 
			//but it has varying alpha values
			//this rgba hex colour is stored in a 2d image for conversion to a open gl texture
			
			float l = UINT8(Turbulance(x, y, anim_counter_, 32)); //turbulance smoothly interoplates along the z point givinig the animation effect
			
			float alpha = l / 255.0; //gets a decimal value of the light value which will be used as the alpha of each pixel
				
			//for some reason my colour to hex function does it backwards (ABGR) so alpha is passed in as the red value
			//I will put this fix on the to do list
			colour_ = Colour_RGBA(alpha*.75, 1, 1, 1);

			image[y][x] = colour_.ToHex();
			
		}
		
	}
	anim_counter_ += dt*speed_;
	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, 4, NOISE_WIDTH, NOISE_HEIGHT, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	return texture;
}

