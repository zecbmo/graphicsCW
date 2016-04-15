#pragma once
#include <string>
#include <iostream>
#include <atomic>
extern std::atomic<bool> scene_loaded;

class Task
{
public:
	Task() { };
	virtual ~Task() {};
	virtual void Run() = 0;

	//inline bool GetTaskComplete() { return task_complete_; };

protected:
	//bool task_complete_;
};

