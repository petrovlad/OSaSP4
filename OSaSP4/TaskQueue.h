#ifndef TASKQUEUE_H

#define TASKQUEUE_H

#include <mutex>
#include <queue>
#include <functional>

typedef std::function<void()> TTask;

class TaskQueue {
private:
	std::queue<TTask> taskQueue;
public:
	TaskQueue();
	void pushTask(const TTask &task);
	void popTask();
	TTask frontTask();
};

#endif
