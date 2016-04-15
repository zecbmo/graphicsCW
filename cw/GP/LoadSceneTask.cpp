#include "LoadSceneTask.h"

void LoadSceneTask::Run()
{
	scene_class_->ThreadFucntion(hdc_, hrc_, hrc2_);
	scene_loaded = true;
}
