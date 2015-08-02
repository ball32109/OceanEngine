#ifndef TASKDISPATCHER_H
#define TASKDISPATCHER_H

#include <list>
#include <queue>
#include "Singleton.h"
#include "TaskBase.h"
#include "Thead.h"


class TaskDispatcher:public Singleton<TaskDispatcher>
{
public:
	typedef std::queue<TaskBase*> TaskQueue;

public:
	TaskDispatcher();
	~TaskDispatcher();

	void		TaskPush(TaskBase* task);
	TaskBase*	TaskPop();

protected:
	TaskQueue		_taskQueue;
	THREAD_MUTEX	_lock;
};


#endif
