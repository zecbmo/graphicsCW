#pragma once

#include "Task.h"
#include <queue>
#include <mutex>
#include <thread>
#include <vector>



class Farm
{
public:
	Farm();
	~Farm();

	void AddTask(Task *task);
	void Run();

private:
	std::mutex queueLock_;
	std::queue<Task*> tasks_;
	std::vector< std::thread* > threads_;
	void WorkerFunction();

};

