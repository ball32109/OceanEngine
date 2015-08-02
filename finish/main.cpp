#include <iostream>
#include <vector>
#include "TaskManager.h"
#include "TaskDispatcher.h"
#include "LuaTask.h"
#include "LogTask.h"
#include "SceneTask.h"
#include "TaskThread.h"
#include "SceneThead.h"

int main() {
	TaskDispatcher* taskDispatcher = new TaskDispatcher();
	TaskManager* taskMgr = new TaskManager();

	typedef std::vector<Thead*> ThreadVector;
	ThreadVector threads;

	LogTask *lt = static_cast<LogTask*>(taskMgr->NewLogTask(NULL));
	taskDispatcher->TaskPush(lt);

	for (int i =0;i < 1000;i++)
	{
		LuaTask *lt = static_cast<LuaTask*>(taskMgr->NewLuaTask("./main.lua"));
		lt->Push(new TaskMessage(i,i));
		taskDispatcher->TaskPush(lt);
	}
	LogTask::GetSingletonPtr()->Log(0,"fuck you:%d",1);
	for (int i = 0;i < 3;i++) {
		Thead* tt = new TashThread();
		tt->Start();
		threads.push_back(tt);
	}

	for (int i = 0;i < 5;i++) {
		SceneTask* st = static_cast<SceneTask*>(taskMgr->NewSceneTask());
		Thead* tt = new SceneThead(st);
		tt->Start();
		threads.push_back(tt);
	}
	
	ThreadVector::iterator it = threads.begin();
	for (;it != threads.end();it++)
	{
		(*it)->Join();
	}
	return 0;
}