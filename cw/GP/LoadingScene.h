#ifndef LOADING_SCENE_
#define LOADING_SCENE_

#include "Scene3D.h"
#include "Noise.h"



class LoadingScene : public Scene3D
{
public:
	LoadingScene();
	~LoadingScene();

	void Init(HWND* hwnd, Input* in, float *dt);
	void Update();
	void Render();	// render scene


private:
	CameraManager camera_manager_;
	Plane loading_screen_;
};



#endif

