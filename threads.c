#include "threads.h"

int threadCreate(Thread *th, ThreadFunc func, Arg a)
{
#ifdef _WIN32
    *th = CreateThread(NULL, 0, func, a, 0, NULL);
    return (th == NULL) ? -1 : 0;
#else
    int retVal = pthread_create(th, NULL, func, a);
    return (retVal != 0) ? -1 : 0;
#endif
}

int threadJoin(Thread th, RetVal *rv)
{
#ifdef _WIN32
    int error = 0;
    int retVal = 0;
    retVal = WaitForSingleObject(th, INFINITE);

    if (retVal == WAIT_FAILED)
        error = 1;

    if (rv != NULL)
    {
        retVal = GetExitCodeThread(th, rv);
        if (retVal == 0)
            error = 1;
    }

    return (error) ? -1 : 0;
#else
    int retVal = pthread_join(th, rv);
    return (retVal != 0) ? -1 : 0;
#endif
}