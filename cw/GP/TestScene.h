#ifndef TEST_SCENE_
#define TEST_SCENE_

#include "Scene3D.h"

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
};



#endif

