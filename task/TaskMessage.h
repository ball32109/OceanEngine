#ifndef TASKMESSAGE_H
#define TASKMESSAGE_H

struct TaskMessage
{
	TaskMessage(int source,int session) {
		_source = source;
		_session = session;
	}
	int		_source;
	int		_session;
	void*	_data;
	int		_size;
};

#endif