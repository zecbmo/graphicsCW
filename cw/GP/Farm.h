#ifndef FARM_H_
#define FARM_H_


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
	void StartTasks();
	void EndTasks();

private:
	std::mutex queueLock_;
	std::queue<Task*> tasks_;
	std::vector< std::thread* > threads_;
	void WorkerFunction();

};

extern Farm farm; //define a global farm created to easily add tasks from different areas of the program
//calling farm.run() will complete all tasks in the queue and can be called from different locations 

#endif