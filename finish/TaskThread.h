#ifndef TASKTHEAD_H
#define TASKTHEAD_H
#include "Thead.h"

class TashThread:public Thead
{
public:
	TashThread();
	~TashThread();

	virtual void Run();
};

#endif