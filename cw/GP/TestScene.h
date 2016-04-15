#ifndef TEST_SCENE_
#define TEST_SCENE_

#include "Scene3D.h"
#include "Noise.h"



class TestScene : public Scene3D
{
public:
	TestScene();
	~TestScene();

	void Init(HWND* hwnd, Input* in, float *dt, HDC	hdc, HGLRC hrc, HGLRC hrc2);
	void ThreadFucntion(HDC	hdc, HGLRC hrc, HGLRC hrc2);
	void Update();
	void Render();	// render scene


private:
	CameraManager camera_manager_;
	Light light_;
	Noise cloud_noise_;
	GLuint text;
	SkyBox sky_box_;
	Shapes disc_;
	Shapes custom_;

	Floor floor_;

	float matrix[16];


	void DrawShadowMatrixScene();
	void GenerateShadowMatrix(float matrix[16], float light_pos[4], GLfloat v0[3], GLfloat v1[3], GLfloat v2[3]);
};



#endif

