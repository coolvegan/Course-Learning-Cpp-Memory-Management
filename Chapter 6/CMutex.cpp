/*******************************************************************************
*
* Portable named or unamed mutex object
*
*******************************************************************************/
#include "stdafx.h"
#include "CMutex.h"

#if IN_WINDOWS
////////////////////////////////////////////////////////////////////////////////
//
void mutex_lock(HANDLE *h)
{
	WaitForSingleObject(*h,INFINITE);
}

////////////////////////////////////////////////////////////////////////////////
//
void mutex_unlock(HANDLE *h)
{
	ReleaseMutex(*h);
}

////////////////////////////////////////////////////////////////////////////////
//
void mutex_init(HANDLE *h,LPVOID,LPVOID name)
{
	*h = CreateMutex(NULL,FALSE,(char *)name);
}

////////////////////////////////////////////////////////////////////////////////
//
void mutex_destroy(HANDLE *h)
{
	CloseHandle(*h);
	*h = NULL;
}

////////////////////////////////////////////////////////////////////////////////
//

static DWORD waitPeriod[] = {47,53,59,61};
static int waitIdx = 0;

/*------------------------------------------------------------------------------
| short mutex_trylock(HANDLE *h)
------------------------------------------------------------------------------*/
short mutex_trylock(HANDLE *h)
{
	DWORD wait = waitPeriod[waitIdx++];
	if(waitIdx > 3)
		waitIdx = 0;
	return (WaitForSingleObject(*h,wait) == WAIT_FAILED) ? 1 : 0;
}

#endif

/******************************************************************************/

////////////////////////////////////////////////////////////////////////////////
//
CMutex::CMutex()
{
	Init();
}

////////////////////////////////////////////////////////////////////////////////
//
CMutex::CMutex(char *name)
{
	Init(name);
}

////////////////////////////////////////////////////////////////////////////////
//
CMutex::~CMutex()
{
	Destroy();
}

////////////////////////////////////////////////////////////////////////////////
//
void CMutex::Lock()
{
	mutex_lock(&Global_mutex);
}

////////////////////////////////////////////////////////////////////////////////
//
void CMutex::Unlock()
{
	mutex_unlock(&Global_mutex);
}

////////////////////////////////////////////////////////////////////////////////
//
int CMutex::TryLock()
{
	return mutex_trylock(&Global_mutex) == 0;
}

////////////////////////////////////////////////////////////////////////////////
//
int CMutex::TryLock(int count)
{
	while(count--) {
		if(TryLock())
			return 1;
	}
	return 0;
}

////////////////////////////////////////////////////////////////////////////////
//
void CMutex::Init()
{
	mutex_init(&Global_mutex,NULL,NULL);
}

////////////////////////////////////////////////////////////////////////////////
//
void CMutex::Init(char *name)
{
	mutex_init(&Global_mutex,NULL,name);
}

////////////////////////////////////////////////////////////////////////////////
//
void CMutex::Destroy()
{
	mutex_destroy(&Global_mutex);
}

#if IN_WINDOWS
/*------------------------------------------------------------------------------
| BOOL CMutex::Exists(char *name)
------------------------------------------------------------------------------*/
BOOL CMutex::Exists(char *name)
{
	HANDLE	test;
	BOOL	fRet = FALSE;
	mutex_init(&test,NULL,name);
	if(test)
		fRet = GetLastError() == ERROR_ALREADY_EXISTS;
	if(!fRet)
		CloseHandle(test);
	return fRet;
}
#endif