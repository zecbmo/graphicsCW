#pragma once
#include "Task.h"
#include "Scene3D.h"

class LoadSceneTask : public Task
{
public:
	LoadSceneTask(HDC hdc, HGLRC hrc, HGLRC hrc2, Scene3D* temp) :hrc_(hrc), hrc2_(hrc2), hdc_(hdc), scene_class_(temp) { };
	void Run();
private:
	Scene3D* scene_class_;
	HGLRC hrc_;
	HGLRC hrc2_;
	HDC hdc_;
};