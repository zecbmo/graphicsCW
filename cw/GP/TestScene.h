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
	void DrawShadowMatrixScene();
	void GenerateShadowMatrix(float matrix[16], float light_pos[4], GLfloat v0[3], GLfloat v1[3], GLfloat v2[3]);
	void RotateLight();
	int RandomNumber(int min, int max);
	void MakeManyCubes();
	CameraManager camera_manager_;
	Light light_;
	
	Light light_point_;
	Light light_point2_;
	Light light_point3_;
	Light light_point4_;

	Light light_spot_;
	Light light_spot2_;



	Noise cloud_noise_;
	GLuint text;
	SkyBox sky_box_;
	Shapes disc_;
	Shapes custom_;

	Sphere sphere_;
	Box box_;

	NewFloor floor_;
	GLuint cubes_;
	float matrix[16];

	GLdouble moveF;
	GLdouble moveR;
	float speed_;
	float timer_;

};



#endif

