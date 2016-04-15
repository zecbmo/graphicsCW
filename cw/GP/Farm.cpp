#include "Farm.h"

Farm::Farm()
{
}


Farm::~Farm()
{
}
void Farm::AddTask(Task *task)
{
	queueLock_.lock();
	tasks_.push(task);
	queueLock_.unlock();
}
void Farm::Run()
{
	int numCores = 4;

	for (int i = 0; i < numCores; i++)
		threads_.push_back(new std::thread(std::mem_fun(&Farm::WorkerFunction), this));

	for (int i = 0; i < numCores; i++)
	{
		threads_[i]->join();
	}

	threads_.clear();
}
void Farm::StartTasks()
{
	int numCores = 2;

	for (int i = 0; i < numCores; i++)
		threads_.push_back(new std::thread(std::mem_fun(&Farm::WorkerFunction), this));
}
void Farm::EndTasks()
{
	for (int i = 0; i < threads_.size(); i++)
	{
		threads_[i]->join();
	}

	threads_.clear();
}
void Farm::WorkerFunction()
{


	while (true)
	{
		queueLock_.lock();


		Task *t = NULL;
		if (!tasks_.empty())
		{
			t = tasks_.front();
			tasks_.pop();
		}
		queueLock_.unlock();

		if (t == NULL)
		{
			break;
		}
		else
		{
			t->Run();
		}


	}

	//another suggestion psudeoish code
	//Task *t = nullptr;
	//do {
	//	{
	//		lock_guard<mutex> lock(queueLock);
	//		if (!queue.empty())
	//			t = queue.pop();
	//	}

	//	if (t != nullptr)
	//		t->run();
	//} while (t != nullptr);


}