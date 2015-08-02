#ifndef THEAD_H
#define THEAD_H


#if defined( __WIN32__ ) || defined( WIN32 ) || defined( _WIN32 )
#include <windows.h> 
#include <process.h>  

#define THREAD_ID											HANDLE
#define THREAD_SINGNAL										HANDLE
#define THREAD_SINGNAL_INIT(x)								x = CreateEvent(NULL, TRUE, FALSE, NULL)
#define THREAD_SINGNAL_DELETE(x)							CloseHandle(x)
#define THREAD_SINGNAL_SET(x)								SetEvent(x)
#define THREAD_MUTEX										CRITICAL_SECTION
#define THREAD_MUTEX_INIT(x)								InitializeCriticalSection(&x)
#define THREAD_MUTEX_DELETE(x)								DeleteCriticalSection(&x)
#define THREAD_MUTEX_LOCK(x)								EnterCriticalSection(&x)
#define THREAD_MUTEX_UNLOCK(x)								LeaveCriticalSection(&x)
#define sleep(x)											Sleep(x)
#else

#define THREAD_ID											pthread_t
#define THREAD_SINGNAL										pthread_cond_t
#define THREAD_SINGNAL_INIT(x)								pthread_cond_init(&x, NULL)
#define THREAD_SINGNAL_DELETE(x)							pthread_cond_destroy(&x)
#define THREAD_SINGNAL_SET(x)								pthread_cond_signal(&x);
#define THREAD_MUTEX										pthread_mutex_t
#define THREAD_MUTEX_INIT(x)								pthread_mutex_init (&x, NULL)
#define THREAD_MUTEX_DELETE(x)								pthread_mutex_destroy(&x)
#define THREAD_MUTEX_LOCK(x)								pthread_mutex_lock(&x)
#define THREAD_MUTEX_UNLOCK(x)								pthread_mutex_unlock(&x)		
#define sleep(x)											usleep(x*1000)

#endif

class Thead {
public:
	Thead();
	~Thead();

	void Start();
	bool Join();

	virtual void Run() {

	}

	virtual void Wait();
	virtual void Wakeup();

	virtual void initCond(void)
	{
		THREAD_SINGNAL_INIT(_cond);
	}

	virtual void initMutex(void)
	{
		THREAD_MUTEX_INIT(_mutex);	
	}

	virtual void deleteCond(void)
	{
		THREAD_SINGNAL_DELETE(_cond);
	}

	virtual void deleteMutex(void)
	{
		THREAD_MUTEX_DELETE(_mutex);
	}

	virtual void lock(void)
	{
		THREAD_MUTEX_LOCK(_mutex); 
	}

	virtual void unlock(void)
	{
		THREAD_MUTEX_UNLOCK(_mutex); 
	}	

#if defined( __WIN32__ ) || defined( WIN32 ) || defined( _WIN32 )
	static unsigned __stdcall threadFunc(void *ctx);
#else
	static void*			  threadFunc(void* ctx);
#endif

protected:
	THREAD_ID		_threadId;
	THREAD_SINGNAL  _cond;		
	THREAD_MUTEX	_mutex;		
};

#endif