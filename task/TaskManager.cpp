#include "TaskManager.h"
#include "LuaTask.h"
#include "SceneTask.h"
#include "LogTask.h"

#include <assert.h>

TaskManager * Singleton< TaskManager >::singleton_ = 0;

TaskManager::TaskManager():_taskMap(),_counter(0)
{
	THREAD_MUTEX_INIT(_lock);
}


TaskManager::~TaskManager()
{
}

TaskBase* TaskManager::NewSceneTask() {
	TaskBase *task = new SceneTask(_counter++);
	_taskMap[task->GetHandle()] = task;
	return task;
}

TaskBase* TaskManager::NewLuaTask(const char* bootFile) {
	TaskBase *task = new LuaTask(bootFile,_counter++);
	_taskMap[task->GetHandle()] = task;
	return task;
}

TaskBase* TaskManager::NewLogTask(const char* logFile) {
	TaskBase *task = new LogTask(logFile,_counter++);
	_taskMap[task->GetHandle()] = task;
	return task;
}

int TaskManager::Send(int destination,TaskMessage* tm) {
	TaskMap::iterator it = _taskMap.find(destination);
	if (it != _taskMap.end()) {
		it->second->Push(tm);
		return 0;
	}
	return -1;
}