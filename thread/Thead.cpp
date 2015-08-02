#include "Thead.h"
#include "../finish/Log.h"
Thead::Thead() {

}

Thead::~Thead() {

}

void Thead::Start() {
#if defined( __WIN32__ ) || defined( WIN32 ) || defined( _WIN32 )
	_threadId = (THREAD_ID)_beginthreadex(NULL, 0, &Thead::threadFunc, (void*)this, NULL, 0);
#else	
	if(pthread_create(&_threadId, NULL, Thead::threadFunc,  (void*)this)!= 0) {
		printf("pthread_create error");
	}
#endif
}

bool Thead::Join() {
#if defined( __WIN32__ ) || defined( WIN32 ) || defined( _WIN32 )
	int i = 0;

	while(true)
	{
		++i;
		DWORD dw = WaitForSingleObject(_threadId, 3000);  

		switch (dw)
		{
		case WAIT_OBJECT_0:
			return true;
		case WAIT_TIMEOUT:
			if(i > 20)
			{
				return false;
			}
			else
			{
				
			}
			break;
		case WAIT_FAILED:
		default:
			return false;
		};
	}
#else
	void* status;
	if(pthread_join(id(), &status))
	{
	
		return false;
	}
#endif
}

#if defined( __WIN32__ ) || defined( WIN32 ) || defined( _WIN32 )
unsigned __stdcall Thead::threadFunc(void *ctx)
#else	
void* Thead::threadFunc(void* ctx)
#endif
{
	Thead * thr = static_cast<Thead*>(ctx);
	LOG_ERROR("thread id:%d,running\n",thr->_threadId);
	thr->Run();
	LOG_ERROR("thread id:%d,dead\n",thr->_threadId);
	return NULL;
}

void Thead::Wait() {
#if KBE_PLATFORM == PLATFORM_WIN32
	WaitForSingleObject(_cond, INFINITE); 
	ResetEvent(_cond);
#else		
	lock();
	pthread_cond_wait(&_cond, &_mutex);
	unlock();
#endif
}

void Thead::Wakeup() {
	THREAD_SINGNAL_SET(_cond);
}