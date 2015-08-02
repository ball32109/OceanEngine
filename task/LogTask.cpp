#include "LogTask.h"
#include "TaskManager.h"
#include <assert.h>

LogTask * Singleton< LogTask >::singleton_ = 0;

#define LOG_MESSAGE_SIZE 256

LogTask::LogTask(const char* file,int handle):TaskBase(handle)
{
	if (file) {
		_fileFd = fopen(file,"w");
		assert(_fileFd != NULL);
	} else {
		_fileFd = stdout;
	}
}


LogTask::~LogTask(void)
{
}

void LogTask::Process(TaskMessage *message) {
	fprintf(_fileFd, "[:%08x] ",message->_source);
	fwrite(message->_data, message->_size , 1, _fileFd);
	fprintf(_fileFd, "\n");
	fflush(_fileFd);

}

void LogTask::Log(int source,const char* msg,...) {
	LogTask& lt = LogTask::GetSingleton();

	char tmp[LOG_MESSAGE_SIZE];
	char *data = NULL;

	va_list ap;

	va_start(ap,msg);
	int len = vsnprintf(tmp, LOG_MESSAGE_SIZE, msg, ap);
	va_end(ap);
	if (len < LOG_MESSAGE_SIZE) {
		data = strdup(tmp);
	} else {
		int maxSize = LOG_MESSAGE_SIZE;
		for (;;) {
			maxSize *= 2;
			data = (char*)malloc(maxSize);
			va_start(ap,msg);
			len = vsnprintf(data, maxSize, msg, ap);
			va_end(ap);
			if (len < maxSize) {
				break;
			}
			free(data);
		}
	}

	TaskMessage* tm = new TaskMessage(source,0);
	tm->_data = data;
	tm->_size = len;
	
	TaskManager::GetSingletonPtr()->Send(lt.GetHandle(),tm);
}