#include "SceneManager.h"

SceneManager::SceneManager()
{
}

SceneManager::~SceneManager()
{
	CleanUp();


}
void SceneManager::Init(HWND* hwnd, Input* input, float* dt)
{
	hwnd_ = hwnd;
	input_ = input;
	dt_ = dt;
	current_scene_ = &test_scene_;
	current_scene_->Init(hwnd_, input_, dt_);
	
}
void SceneManager::Update()
{
	if (current_scene_->GetSceneToLoad() != current_scene_type_)
	{
		LoadScene();
	}

	current_scene_->Update();
}
void SceneManager::LoadScene()
{
	current_scene_type_ = current_scene_->GetSceneToLoad();

	switch (current_scene_type_)
	{
	case TESTING_SCENE:
		current_scene_ = &test_scene_;		
		break;
	case OPTIONS_SCENE:
		break;
	case LEVEL_SCENE:
		break;
	case BASE_SCENE:
		current_scene_ = &base_scene_;
		break;
	default:
		break;
	}
	current_scene_->Init(hwnd_, input_, dt_);
}
void SceneManager::CleanUp()
{
	
}

