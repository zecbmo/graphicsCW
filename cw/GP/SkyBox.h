#pragma once

#include <windows.h>
#include <stdio.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include "ErrorSystem.h"
#include "SOIL.h"
#include <string>
#include "Vector3.h"
#include "Shapes.h"

enum SkyBoxType {CUBE_SKY, SPHERE_SKY, CUBE_SIX};
class SkyBox
{
public:
	SkyBox() {};
	~SkyBox() {};

	void Init(SkyBoxType type, std::string filename);
	void InitCubeBox(std::string ft, std::string lf, std::string rt, std::string bk, std::string up, std::string dn);
	void Render(Vector3 camera_position);

private:
	void Draw();
	void MakeCube();
	GLuint cube_;
	GLuint texture_, ft_, lf_, rt_, bk_, up_t_, dn_;
	SkyBoxType type_;
	Shapes shape_, front_, left_, right_, back_, up_, down_, face_;
};

