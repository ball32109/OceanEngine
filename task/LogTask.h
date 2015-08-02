#ifndef LOGTASK_H
#define LOGTASK_H
#include "TaskBase.h"
#include "Singleton.h"

class LogTask:public TaskBase,public Singleton<LogTask>
{
public:
	LogTask(const char* file,int handle);
	~LogTask();

	virtual void Process(TaskMessage *message);

	static void Log(int source,const char* msg,...);

protected:
	FILE* _fileFd;
};

#endif