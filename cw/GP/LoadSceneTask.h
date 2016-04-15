#pragma once
#include "Task.h"
#include "Scene3D.h"

class LoadSceneTask : public Task
{
public:
	LoadSceneTask(Scene3D* temp) : scene_class_(temp) { };
	void Run();
private:
	Scene3D* scene_class_;

};