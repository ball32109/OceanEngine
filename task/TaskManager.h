#ifndef TASKMANAGER_H
#define TASKMANAGER_H
#include <map>
#include "Thead.h"
#include "Singleton.h"
#include "TaskBase.h"

class TaskManager:public Singleton<TaskManager>
{
public:
	typedef std::map<int,TaskBase*> TaskMap;
	enum WhatTask {
		Lua = 0,
		Scene
	};
public:
	TaskManager();
	~TaskManager();

	TaskBase* NewSceneTask();
	TaskBase* NewLuaTask(const char* bootFile);
	TaskBase* NewLogTask(const char* logFile);

	int Send(int destination,TaskMessage* tm);

protected:
	TaskMap			_taskMap;
	int				_counter;
	THREAD_MUTEX	_lock;
};

#endif
