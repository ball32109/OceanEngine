#ifndef LUATASK_H
#define LUATASK_H
#include "TaskBase.h"
extern "C"{
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
};

class LuaTask:public TaskBase
{
public:
	LuaTask(const char* bootFile,int handle);
	~LuaTask();

	virtual void Process(TaskMessage* tm);

	static int SetCallBack(lua_State* L);
	static int Log(lua_State* L);
	static int Pack(lua_State* L);
	static int UnPack(lua_State* L);
	static int Send(lua_State* L);
protected:
	lua_State* _L;
	int _callBackIndex;
};

#endif