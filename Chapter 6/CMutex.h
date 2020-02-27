#if !defined(_H_CMUTEX)
#define _H_CMUTEX

#if defined(__WIN32__) || defined(_WIN32) || defined(WIN32)
#define IN_WINDOWS 1
#else
#define IN_WINDOWS 0
#endif

#if IN_WINDOWS
#include <windows.h>
#else
#define _REENTRANT
#include <stdlib.h>
#include <stdio.h>
#include <thread.h>
#include <errno.h>
#include <malloc.h>
#include <memory.h>
#include <string.h>
#include <pthread.h>
#include <synch.h>
#include <unistd.h>
#endif

class CMutex {
protected:

	virtual	void	Lock();
	virtual	void	Unlock();
	virtual	int		TryLock();
	virtual int		TryLock(int);
	virtual void	Destroy();

public:
#if IN_WINDOWS
	HANDLE			Global_mutex;
#else
	mutex_t			Global_mutex;
#endif

					CMutex();
					CMutex(char *);
	virtual			~CMutex();
#if IN_WINDOWS
	static BOOL		Exists(char *);
#endif
	virtual	void	Init();
	virtual void	Init(char *);
	virtual void	Get() {Lock();}
	virtual void	Release(){Unlock();}
	virtual int		Try(){return TryLock();}
};

#endif
//
//
//