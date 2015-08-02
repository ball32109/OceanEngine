#ifndef SCENETHEAD_H
#define SCENETHEAD_H
#include "Thead.h"
#include "TaskBase.h"
class SceneThead:public Thead
{
public:
	SceneThead(TaskBase* task);
	~SceneThead();

	virtual void Run();

protected:
	TaskBase* _task;
};

#endif