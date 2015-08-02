#include "TaskThread.h"
#include "TaskDispatcher.h"
#include "Log.h"

TashThread::TashThread()
{
}


TashThread::~TashThread()
{
}

void TashThread::Run() {
	TaskDispatcher* td = TaskDispatcher::GetSingletonPtr();
	TaskBase* task;
	for(;;) {
		task = td->TaskPop();
		if (task == NULL) {
			sleep(1);
		} else {
			for (;;) {
				TaskMessage* tm = task->Pop();
				if (tm != NULL) {
					task->Process(tm);
				} else {
					task->SetInDispatcher(false);
					break;
				}
			}
			
		}
	}
}
