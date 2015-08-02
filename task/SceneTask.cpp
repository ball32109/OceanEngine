#include "SceneTask.h"
#include "Log.h"

SceneTask::SceneTask(int handle):TaskBase(handle)
{
}


SceneTask::~SceneTask(void)
{
}

void SceneTask::Push(TaskMessage *message) {
	THREAD_MUTEX_LOCK(_lock);
	_messageQueue.push(message);
	THREAD_MUTEX_UNLOCK(_lock);
}

void SceneTask::Process(TaskMessage* tm) {
	LOG("process scene task!\n");
	printf("scene source:%d,session:%d",tm->_source,tm->_session);
}