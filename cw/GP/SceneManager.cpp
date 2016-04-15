#include "SceneManager.h"

Farm farm; //declare farm here as it is first class that uses it
std::atomic<bool> scene_loaded = false;
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
	current_scene_ = new TestScene;	
	current_scene_->Init(hwnd_, input_, dt_);	
	current_scene_type_ = current_scene_->GetSceneToLoad();
	loading_scene_ = new LoadingScene;
	loading_scene_->Init(hwnd_, input_, dt_);
	loading_ = false;
}
void SceneManager::Update()
{
	if (current_scene_->GetSceneToLoad() != current_scene_type_)
	{
		LoadScene();
	}
	wglMakeCurrent(current_scene_->hdc, current_scene_->hrc);
	if (loading_ && scene_loaded)
	{
		
		current_scene_ = scene_to_load_;
		scene_to_load_ = NULL;
		farm.EndTasks();
		current_scene_->Init(hwnd_, input_, dt_);
		current_scene_type_ = current_scene_->GetSceneToLoad();		
		loading_ = false; //local conrtoller
		scene_loaded = false; //global conrtoller
	}
	
	current_scene_->Update();
	

	

	
}
void SceneManager::LoadScene()
{
	scene_to_load_type_ = current_scene_->GetSceneToLoad();
	current_scene_type_ = LOADING_SCENE;
	delete current_scene_;
	switch (scene_to_load_type_)
	{
	case TESTING_SCENE:
		scene_to_load_ = new TestScene;
		break;
	case OPTIONS_SCENE:
		break;
	case LEVEL_SCENE:
		break;
	case BASE_SCENE:
		scene_to_load_ = new Scene3D;
		break;
	case EARTH_SCENE:
		scene_to_load_ = new EarthScene;
		break;
	case TRON_SCENE: 
		scene_to_load_ = new TronScene;
		break;
	default:
		break;
	}

	current_scene_ = loading_scene_;
	

	//add the loading 
	farm.AddTask(new LoadSceneTask(scene_to_load_));
	//add update task to display loading screen
	//farm.AddTask(new DisplayLoadingScreen(current_scene_));
	farm.StartTasks();
	loading_ = true;
	
	
}
void SceneManager::CleanUp()
{
	delete loading_scene_;
	loading_scene_ = NULL;

	delete current_scene_;
	current_scene_ = NULL;
}
void SceneManager::Resize()
{
	current_scene_->Resize();

}

