#include "Noise.h"
#include "NoiseTexTask.h"
#include "NoiseSmoothTask.h"
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

float Noise::SmoothNoise(float x, float y, float z)
{
	//get fractal
	float fract_x = x - int(x);
	float fract_y = y - int(y);
	float fract_z = z - int(z);

	//wrap arround
	int x1 = (int(x) + NOISE_WIDTH) % NOISE_WIDTH;
	int y1 = (int(y) + NOISE_HEIGHT) % NOISE_HEIGHT;
	int z1 = (int(z) + NOISE_DEPTH) % NOISE_DEPTH;

	//neighbour values
	int x2 = (x1 + NOISE_WIDTH - 1) % NOISE_WIDTH;
	int y2 = (y1 + NOISE_HEIGHT - 1) % NOISE_HEIGHT;
	int z2 = (z1 + NOISE_DEPTH - 1) % NOISE_DEPTH;

	//smooth with bi-linear interpolation (we learnt this in class)
	float value = 0.0f;

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

void Noise::ThreadSmoothNoise(float x, float y, float z, float size, float* value)
{
	*value += SmoothNoise(x / size, y / size, z / size) * size;
		
}

float Noise::Turbulance(float x, float y, float z, float size)
{
	float value = 0.0f;
	float initial_size = size;

	//std::vector<std::thread*> threads;

	//while (size >= 1)
	//{
	//	threads.push_back(new std::thread(&Noise::ThreadSmoothNoise,this, x, y, z, size, &value));
	//	size /= 2.0;
	//}

	//for (int i = 0; i < threads.size(); i++)
	//{
	//	threads[i]->join();
	//}	


	//for (int y = 0; y < NOISE_HEIGHT; y++)
	//{
	//	smooth_farm_.AddTask(new NoiseSmoothtask(x, y, z, size, &value, this));
	//}

	//smooth_farm_.Run();

	while (size >= 1)
	{
		value += SmoothNoise(x / size, y / size, z / size) * size;
		size /= 2.0;
	}

	return(128.0f * value / initial_size);
}

GLuint Noise::GetCloudNoiseTexture(float dt)
{
	
		
	//the noise code is based off of Hue, Saturation and light
	//I have modified it so it is based off of a pure white texture 
	//but it has varying alpha values
	//this rgba hex colour is stored in a 2d image for conversion to a open gl texture

	//As this is to represent clouds, we want large parts of the texture to be fully clear
	//so any texel that has an alpha of less than 0.4 gets culled

	//with the remaining texels starting them with an alpha of 0.4 makes it very jaged (not cloud like)
	//so it is scalled so that all remain values lie between 0 and one
	//ie 0.4 will be 0
	//0.8 will be 1 (this is quick a fix but effective for gaining more clouds in the texture rather than one giant cloud covering the earth )


	// Start timing
	the_clock::time_point start = the_clock::now();

	//for (int y = 0; y < NOISE_HEIGHT; y++)
	//{
	//	for (int x = 0; x < NOISE_WIDTH; x++)
	//	{			
	//		float light = UINT8(Turbulance(x, y, anim_counter_, 16)); //turbulance smoothly interoplates along the z point givinig the animation effect
	//		
	//		float alpha = (light / 255.0)*1; //gets a decimal value of the light value which will be used as the alpha of each pixel
	//			
	//		if (alpha < 0.4) //culling
	//		{
	//			alpha = 0; 
	//		}
	//		else
	//		{				
	//			alpha = (alpha * 2.5 )- 1; //making a wide range of remaining values
	//		}
	//	
	//		if (alpha > 1)
	//		{
	//			alpha = 1; //making the top value stay in range
	//		}

	//		//for some reason my colour to hex function does it backwards (ABGR) so alpha is passed in as the red value
	//		//I will put this fix on the to do list
	//		colour_ = Colour_RGBA(alpha, 1, 1, 1);
	//		image[y][x] = colour_.ToHex();			
	//	}	
	//}

	int amount = 4;

	for (int y = 0; y < NOISE_HEIGHT; y+=amount)
	{
		tex_farm_.AddTask(new NoiseTextask(y, amount, this));
	}

	tex_farm_.Run();

	the_clock::time_point end = the_clock::now();

	 //Compute the difference between the two times in milliseconds
	auto time_taken = duration_cast<milliseconds>(end - start).count();

	//collect a wide range of times 
	int size = times_.size();

	if (times_.size() < 10000)
	{
		times_.push_back(time_taken);
	}

	anim_counter_ += dt*speed_;

	//the follow creates the texture from the 2d array of pixel data
	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, 4, NOISE_WIDTH, NOISE_HEIGHT, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	return texture;
}

void Noise::WriteCollectedDataToFile()
{
	int lowest = 100000000;
	int highest = 0;
	int total = 0;
	int size = times_.size();
	
	std::ofstream output;
	output.open("data.txt");

	output << "Data Collection of times taken to generate " << size << " noise textures in miliseconds.\n\n";
	output << "List of idividual times.\n";

	for (int i = 0; i < size; i++)
	{
		if (times_[i] < lowest)
		{
			lowest = times_[i];
		}
		if (times_[i] > highest)
		{
			highest = times_[i];
		}

		total += times_[i];
		
		output << times_[i] << "\n";

		
	}

	float mean = total / size;

	output << "\nFastest time: " << lowest << "\n";
	output << "Slowest time: " << highest << "\n";
	output << "Total time for " << size << " loops: " << total << "\n";
	output << "Mean time: " << mean << "\n";

	output.close();


}

void Noise::TexGenHelper(int y_pos, int amount)
{
	for (int i = y_pos; i < (y_pos + amount); i++)
	{
		for (int x = 0; x < NOISE_WIDTH; x++)
		{
			float light = UINT8(Turbulance(x, i, anim_counter_, 16)); //turbulance smoothly interoplates along the z point givinig the animation effect

			float alpha = (light / 255.0) * 1; //gets a decimal value of the light value which will be used as the alpha of each pixel

			if (alpha < 0.4) //culling
			{
				alpha = 0;
			}
			else
			{
				alpha = (alpha * 2.5) - 1; //making a wide range of remaining values
			}

			if (alpha > 1)
			{
				alpha = 1; //making the top value stay in range
			}

			//for some reason my colour to hex function does it backwards (ABGR) so alpha is passed in as the red value
			//I will put this fix on the to do list		
			image[i][x] = Colour_RGBA(alpha, 1, 1, 1).ToHex();
		}
	}
}

