#ifndef SCENETASK_H
#define SCENETASK_H
#include "TaskBase.h"

class SceneTask:public TaskBase
{
public:
	SceneTask(int handle);
	~SceneTask();

	virtual void Push(TaskMessage *message);

	virtual void Process(TaskMessage* tm);
};

#endif