#pragma once

#include <vector>
#include <iterator>
#include <string>
#include <set>
#include <cmath>
#include <time.h>
#include "SOIL.h"
#include <iostream>
#include <thread>
#include <windows.h>
#include <stdio.h>
#include <mmsystem.h>
#include <math.h>
#include <gl/gl.h>
#include <gl/glu.h>

#include <string>


class BitmapTextRenderer
{
public:
	BitmapTextRenderer();
	~BitmapTextRenderer();
	void init(std::string filename);
	void drawText(std::string text, float x, float y, float charWidth, float charHeight);


private: 
	GLuint fontTexture;

};

