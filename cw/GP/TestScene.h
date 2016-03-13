#ifndef TEST_SCENE_
#define TEST_SCENE_

#include "Scene3D.h"
#include "Noise.h"


class TestScene : public Scene3D
{
public:
	TestScene();
	~TestScene();

	void Init(HWND* hwnd, Input* in, float *dt);
	void Update();
	void Render();	// render scene


private:
	CameraManager camera_manager_;
	Light light_;
	Noise cloud_noise_;
	GLuint text;
	SkyBox sky_box_;
	Shapes disc_;

	bool wireframe_;


};



#endif

