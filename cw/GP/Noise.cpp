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

	while (size >= 1)
	{
		value += SmoothNoise(x / size, y / size, z / size) * size;
		size /= 2.0;
	}

	return(128.0f * value / initial_size);

	return 0.0f;
}

Colour_RGBA Noise::HSLtoRGBA(double h, double s, double l)
{
	double r, g, b;

	if (s == 0) {
		r = g = b = l; // achromatic
	}
	else 
	{
		double q = l < 0.5 ? l * (1 + s) : l + s - l * s;
		double p = 2 * l - q;
		r = HUEtoRGB(p, q, h + 1 / 3);
		g = HUEtoRGB(p, q, h);
		b = HUEtoRGB(p, q, h - 1 / 3);
	}
	double a = l / 100.0;
	return Colour_RGBA(r, g, b, a);
}
float Noise::HUEtoRGB(double p, double q, double t) 
{
	if (t < 0) t += 1;
	if (t > 1) t -= 1;
	if (t < 1 / 6) return p + (q - p) * 6 * t;
	if (t < 1 / 2) return q;
	if (t < 2 / 3) return p + (q - p) * (2 / 3 - t) * 6;
	return p;
}

GLuint Noise::GetCloudNoiseTexture()
{
	uint32_t image[NOISE_HEIGHT][NOISE_WIDTH];

	for (int y = 0; y < NOISE_HEIGHT; y++)
	{
		for (int x = 0; x < NOISE_WIDTH; x++)
		{
			//converts a HSL colour to a pixel point from the noise
			float l = UINT8(Turbulance(x, y, 0, 32));
			l = l / 255.0;
			colour_ = Colour_RGBA(1, 1, 1, l);//HSLtoRGBA(169, 255, l);

			image[y][x] = colour_.ToHex();

		}
	}
	 
	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, 4, NOISE_WIDTH, NOISE_HEIGHT, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	return texture;
}

