#pragma once

#include <windows.h>
#include <stdio.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include "ErrorSystem.h"
#include "SOIL.h"
#include <string>
#include "Vector3.h"

enum SkyBoxType {CUBE_SKY, SPHERE_SKY};
class SkyBox
{
public:
	SkyBox() {};
	~SkyBox() {};

	void Init(SkyBoxType type, std::string filename);
	void Render(Vector3 camera_position);

private:
	void Draw();
	void MakeCube();
	GLuint cube_;
	GLuint texture_;
	SkyBoxType type_;
};

