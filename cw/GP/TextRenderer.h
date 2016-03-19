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
#include "ErrorSystem.h"
#include <string>
#include "BaseColour.h"

class BitmapTextRenderer
{
public:
	BitmapTextRenderer();
	~BitmapTextRenderer();
	void Init(std::string filename);
	void DrawString(std::string text, float x, float y, float charWidth, float charHeight);
	inline void SetColour(Colour_RGBA colour) { colour_ = colour; };
	inline Colour_RGBA GetColour() { return colour_; };

private: 
	GLuint fontTexture_;
	Colour_RGBA colour_;

};

