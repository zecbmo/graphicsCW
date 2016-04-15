#include "SceneManager.h"

Farm farm; //declare farm here as it is first class that uses it

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
	current_scene_ = new LoadingScene;	
	current_scene_->Init(hwnd_, input_, dt_);	
	current_scene_type_ = current_scene_->GetSceneToLoad();
}
void SceneManager::Update()
{
	if (current_scene_->GetSceneToLoad() != current_scene_type_)
	{
		LoadScene();
	}

	///farm add update for loading 
	//farm you add init for other

	//2 threads to signal

	

	current_scene_->Update();
}
void SceneManager::LoadScene()
{
	current_scene_type_ = current_scene_->GetSceneToLoad();
	delete current_scene_;
	switch (current_scene_type_)
	{
	case TESTING_SCENE:
		current_scene_ = new TestScene;
		break;
	case OPTIONS_SCENE:
		break;
	case LEVEL_SCENE:
		break;
	case BASE_SCENE:
		current_scene_ =  new Scene3D;
		break;
	case EARTH_SCENE:
		current_scene_ = new EarthScene;
		break;
	case TRON_SCENE: 
		current_scene_ = new TronScene;
		break;
	default:
		break;
	}

	if (current_scene_->IsLoaded())
	{
		current_scene_->SetSceneToLoad(current_scene_type_); 
		//sets the enum type to match the scene being loaded. 
		//eg if tests scene loads the base scene... it's scene to load variable becomes BASE_SCENE
		//when we reload test scene this needs to be switched back to TEST_SCENE
	}
	else
	{
		//create two threads. 
		//one that initialises the scene
		//one that displays a loading screen
		//the init thread will signal to the other thread when it is finished loading
		//the init thread will continue on as the main thread

		current_scene_->Init(hwnd_, input_, dt_);
	}
}
void SceneManager::CleanUp()
{
	delete current_scene_;
	current_scene_ = NULL;
}
void SceneManager::Resize()
{
	current_scene_->Resize();

}

