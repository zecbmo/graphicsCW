#ifndef SCENE_MANAGER_
#define SCENE_MANAGER_

#include <windows.h>
#include <stdio.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include "ErrorSystem.h"
#include "Scene3D.h"
#include "TestScene.h"
#include "EarthScene.h"
#include "TronScene.h"
#include "LoadingScene.h"
#include "LoadSceneTask.h"




class SceneManager
{
public:
	SceneManager();
	~SceneManager();

	void Init(HWND* hwnd, Input* input, float* dt);
	void Update();
	void Resize(); 
	

private:
	SceneType current_scene_type_;
	SceneType scene_to_load_type_;

	Scene3D* current_scene_;
	Scene3D* loading_scene_;
	Scene3D*  scene_to_load_;
	void LoadScene();
	void CleanUp();
	//used for initialisation of scenes
	HWND* hwnd_;
	Input* input_;
	float* dt_;
	bool loading_;
	//list of different scenes in game

};




#endif
