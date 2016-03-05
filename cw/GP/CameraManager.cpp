#include "CameraManager.h"

CameraManager::CameraManager()
{
}

CameraManager::~CameraManager()
{
	CleanUp();
}
void CameraManager::Init(Input* input, float* dt, RECT* screen_rect, HWND* hwnd)
{
	input_ = input;
	dt_ = dt;
	screen_rect_ = screen_rect;
	hwnd_ = hwnd;
}
void CameraManager::CreateCamera(CameraType type, std::string tag)
{
	if (CheckTagExists(tag)) //will throw an error if the tag is linked with another camera
	{
		error::StringError(tag, ": Camera with tag already exists");
	}
	switch (type)
	{
	case FIXED_POSITION:
	{
		Camera* fixed = new Camera;
		fixed->Init(input_, dt_, screen_rect_, hwnd_, tag);
		camera_list_.push_back(fixed);
	}
		break;
	case FLOATING:	
	{
		FloatingCamera* floating = new FloatingCamera;
		floating->Init(input_, dt_, screen_rect_, hwnd_, tag);
		camera_list_.push_back(floating);
	}
		break;
	case ROTATING:
	{
		RotatingCamera* rot = new RotatingCamera;
		rot->Init(input_, dt_, screen_rect_, hwnd_, tag);
		camera_list_.push_back(rot);	
	}
		break;
	case SCROLLING:
	{
		//Additions to be made at a later date
	}
		break;
	case MOVABLE:
	{
		//Additions to be made at a later date
	}
		break;
	case TRACKING:
	{
		//Additions to be made at a later date
	}
		break;
	case PUSHABLE:
	{

	}
		break;
	case FIRST_PERSON:
	{
		FPSCamera* fps = new FPSCamera;
		fps->Init(input_, dt_, screen_rect_, hwnd_, tag);
		camera_list_.push_back(fps);
	}
		break;
	default:		
		error::StringError(tag, ": The Type for this Camera Does not exist");
		break;
	}
}

void CameraManager::DeleteCamera(std::string tag)
{
	if (!CheckTagExists(tag))
	{
		error::StringError(tag, ": Camera Does not exist: DeleteCamera()");
	}
	int i = 0;
	for (auto iter : camera_list_)
	{
		if (iter->GetTag() == tag)
		{
			camera_list_.erase(camera_list_.begin()+i);
			delete iter;
			iter = NULL;
			return;
		}
		i++;
	}
}
Camera* CameraManager::CurrentCamera()
{
	return current_camera_;
}
Camera* CameraManager::GetCamera(std::string tag)
{
	if (!CheckTagExists(tag))
	{
		error::StringError(tag, ": Camera Does not exist: GetCamera()");
	}
	for (auto iter : camera_list_)
	{
		if (iter->GetTag() == tag)
		{
			return iter;
		}
	}
}
void CameraManager::ChangeCamera(std::string tag)
{
	if (!CheckTagExists(tag))
	{
		error::StringError(tag, ": Camera Does not exist: ChangeCamera()");
	}
	for (auto iter : camera_list_)
	{
		if (iter->GetTag() == tag)
		{
			current_camera_ = iter;
			return;
		}
	}
}


void CameraManager::Update()
{
	current_camera_->Update();
}
void CameraManager::Render()
{
	current_camera_->Render();
}


void CameraManager::CleanUp()
{

	for (Camera* iter : camera_list_)
	{
		delete iter;
	}
	//current camera deleted through the above for loop
	current_camera_ = NULL;
	
}
bool CameraManager::CheckTagExists(std::string tag)
{
	for (auto iter : camera_list_)
	{
		if (iter->GetTag() == tag)
		{
			return true;
		}
	}

	return false;
	

}