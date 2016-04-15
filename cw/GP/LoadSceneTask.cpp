#include "LoadSceneTask.h"

void LoadSceneTask::Run()
{
	scene_class_->ThreadFucntion();
	scene_loaded = true;
}
