#include "SceneThead.h"
#include "TaskMessage.h"


SceneThead::SceneThead(TaskBase* task):_task(task)
{
}


SceneThead::~SceneThead(void)
{
}

void SceneThead::Run() {
	for(;;) {
		TaskMessage* tm = _task->Pop();
		if (tm == NULL) {
			sleep(1);
		} else {
			_task->Process(tm);
		}
	}
}