#include "TaskBase.h"
#include "TaskDispatcher.h"

TaskBase::TaskBase(int handle):_handle(handle),_messageQueue(),_inDispatcher(false)
{
	THREAD_MUTEX_INIT(_lock);
}


TaskBase::~TaskBase(void)
{
}

TaskMessage* TaskBase::Pop() {
	THREAD_MUTEX_LOCK(_lock);
	TaskMessage* message = NULL;
	if (!_messageQueue.empty()) {
		message = _messageQueue.front();
		_messageQueue.pop();
	}
	THREAD_MUTEX_UNLOCK(_lock);
	
	if (message)
		_inDispatcher = false;
	
	return message;
}

void TaskBase::Push(TaskMessage *message) {
	THREAD_MUTEX_LOCK(_lock);
	_messageQueue.push(message);
	if (_inDispatcher == false) {
		_inDispatcher = true;
		TaskDispatcher* dispatcher = TaskDispatcher::GetSingletonPtr();
		dispatcher->TaskPush(this);
	}
	THREAD_MUTEX_UNLOCK(_lock);
}

void TaskBase::Process(TaskMessage *message) {

}