#ifndef TASKBASE_H
#define TASKBASE_H

#include <queue>
#include "Thead.h"
#include "TaskMessage.h"


class TaskBase
{
public:
	typedef std::queue<TaskMessage*> MessageQueue;
public:
	TaskBase(int handle);
	virtual ~TaskBase();

	TaskMessage*	Pop();
	virtual void	Push(TaskMessage *message);
	virtual void	Process(TaskMessage *message);

	int GetHandle() {
		return _handle;
	}

	void SetInDispatcher(bool yes) {
		_inDispatcher = yes;
	}

protected:
	int				_handle;
	THREAD_MUTEX	_lock;
	MessageQueue	_messageQueue;
	bool			_inDispatcher;
};	

#endif