#include "TaskDispatcher.h"

TaskDispatcher * Singleton< TaskDispatcher >::singleton_ = 0;

TaskDispatcher::TaskDispatcher():_taskQueue()
{
	THREAD_MUTEX_INIT(_lock);
}


TaskDispatcher::~TaskDispatcher(void)
{
}

void TaskDispatcher::TaskPush(TaskBase* task) {
	THREAD_MUTEX_LOCK(_lock);
	_taskQueue.push(task);
	THREAD_MUTEX_UNLOCK(_lock);
}

TaskBase* TaskDispatcher::TaskPop() {
	THREAD_MUTEX_LOCK(_lock);
	TaskBase* task = NULL;
	if (!_taskQueue.empty()) {
		task = _taskQueue.front();
		_taskQueue.pop();
	}
	THREAD_MUTEX_UNLOCK(_lock);
	return task;
}