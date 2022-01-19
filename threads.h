#ifndef THREADS_H
#define THREADS_H

#ifdef _WIN32
 #include <Windows.h>
 typedef HANDLE Thread;
 typedef LPVOID Arg;
 typedef DWORD RetVal;
 typedef RetVal (*ThreadFunc)(Arg);
#else
 #include <pthread.h>
 typedef pthread_t Thread;
 typedef void *Arg;
 typedef void *RetVal;
 typedef RetVal (*ThreadFunc)(Arg);
#endif

int threadCreate(Thread *th, ThreadFunc func, Arg a);
int threadJoin(Thread th, RetVal *rv);

#endif // THREADS_H