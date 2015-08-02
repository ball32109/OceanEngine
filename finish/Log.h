#ifndef LOG_H
#define LOG_H
#include <stdio.h>
class Log
{
public:
	Log();
	~Log();
};

#define LOG_ERROR(A,B) fprintf(stderr,A,B)
#define LOG(A) fprintf(stderr,A)
#endif