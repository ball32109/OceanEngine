#include "LuaTask.h"
#include "Log.h"
#include "LogTask.h"

LuaTask::LuaTask(const char* bootFile,int handle):TaskBase(handle),_callBackIndex(0)
{
	_L = luaL_newstate();
	luaL_openlibs(_L);

	int r = luaL_loadfile(_L,bootFile);
	if (r != LUA_OK) {
		LOG_ERROR("error load file:%s,error:%s",bootFile,luaL_tostring(_L,-1));
	}
	lua_newtable(_L);

	lua_pushlightuserdata(_L,this);
	lua_pushcclosure(_L,LuaTask::SetCallBack,1);
	lua_setfield(_L,-2,"SetCallBack");

	lua_pushlightuserdata(_L,this);
	lua_pushcclosure(_L,LuaTask::Log,1);
	lua_setfield(_L,-2,"Log");

	lua_pushcfunction(_L,LuaTask::Pack);
	lua_setfield(_L,-2,"Pack");

	lua_pushcfunction(_L,LuaTask::UnPack);
	lua_setfield(_L,-2,"UnPack");

	lua_pushlightuserdata(_L,this);
	lua_pushcclosure(_L,LuaTask::Send,1);
	lua_setfield(_L,-2,"Send");

	lua_setglobal(_L,"Finish");


	r = lua_pcall(_L,0,0,0);
	if (r != LUA_OK) {
		LOG_ERROR("error load file:%s,error:%s",bootFile,luaL_tostring(_L,-1));
	}
}


LuaTask::~LuaTask()
{
}

void LuaTask::Process(TaskMessage* tm) {
	lua_rawgeti(_L, LUA_REGISTRYINDEX, _callBackIndex);
	lua_pushinteger(_L,tm->_source);
	lua_pushinteger(_L,tm->_session);
	int r = lua_pcall(_L,2,0,0);
	if (r != LUA_OK) {
		fprintf(stderr,"error call lua:%s",lua_tostring(_L,-1));
	}
}

int LuaTask::SetCallBack(lua_State* L) {
	LuaTask* lt = (LuaTask*)lua_touserdata(L, lua_upvalueindex(1));
	int r = luaL_ref(L, LUA_REGISTRYINDEX);
	lt->_callBackIndex = r;
	return 0;
}

int LuaTask::Log(lua_State* L) {
	LuaTask* lt = (LuaTask*)lua_touserdata(L, lua_upvalueindex(1));
	LogTask& logTask = LogTask::GetSingleton();
	logTask.Log(lt->GetHandle(),"%s", luaL_checkstring(L,1));
	return 0;
}

int LuaTask::Pack(lua_State* L) {
	return 0;
}

int LuaTask::UnPack(lua_State* L) {
	return 0;
}

int LuaTask::Send(lua_State* L) {
	LuaTask* lt = (LuaTask*)lua_touserdata(L, lua_upvalueindex(1));
	return 0;
}