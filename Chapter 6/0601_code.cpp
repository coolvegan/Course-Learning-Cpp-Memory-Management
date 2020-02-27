#include "CMutex.h"

////////////////////////////////////////////////////////////////
class CMutexHelper {
public:    
    CMutexHelper(CMutex *mutex) : m_mutex(mutex), m_locked(false) 
    {
        lock();
    }

    CMutexHelper() : m_mutex(NULL), m_locked(false)
    {
    }

    void use(CMutex *mutex)
    {
        m_mutex = mutex;
        lock();
    }

#if !defined(TRY_ONLY)    
    bool try(CMutex *mutex = NULL) 
    {
        if (mutex) {
            m_mutex = mutex;
        }
        m_locked = (m_mutex) ? m_mutex->Try() : false;
        return m_locked;
    }
#endif

    ~CMutexHelper()
    {
        if (m_mutex && m_locked) {
            m_mutex->Release();
        }
    }

    bool isLocked() { return m_locked; }
private:
    CMutex *m_mutex;
    bool m_locked;    

    void lock()
    {
        if (m_mutex) {
#if defined(TRY_ONLY)
            m_locked = m_mutex->Try();
            if (!m_locked) {
                throw 1;
            }
#else
            m_locked = true;
            m_mutex->Lock();
#endif
        }
    }

};

void MyClass::SynchedMethod()
{
    CMutexHelper mth;

    try {
        mth->use(&m_myMutex);
        DoSomethingWithSynchAsset();
        SomeMoreCode();
    }
    catch (int) {
        // Log it or deal with it some other way
    }
}

void MyClass::OtherSynchedMethod()
{
    CMutexHelper mth;

    try {
        mth->use(&m_myMutex);
        DoSomethingElseWithSynchAsset();
        StillAnotherFunctionCall();
    }
    catch (int) {
        // Log it or deal with it some other way
    }
}

// Separate the synchronization from the actual work via
// private and public interfaces:

void MyClass::SynchronizedMethod()
{
    CMutexHelper mth;

    try {
        mth->use(&m_myMutex);
        private_workMethod();
    }
    catch (int) {
        // Log it or deal with it some other way
    }
}

void MyClass::private_workMethod()
{
    DoSomethingWithSynchAsset();
    SomeMoreCode();
}

class CMutexUser {
public:    
    CMutexUser() {}

    virtual ~CMutexUser() 
    {
        release();
    }

    bool try() {
        return (m_mutex.isLocked()) ? true : m_mutex.Try();
    }

    bool release()
    {
        if (m_mutex.isLocked()) {
            m_mutex.Release();
        }
    }

private:
    CMutex m_mutex;
};

class MyMutexedClass : public CMutexUser {

    MyMutexedClass () : CMutexUser()
    {

    }

    virtual ~MyMutexedClass()
    {
        // ... reminder : if not virtual, mutex isn't auto-released
    }

    void someMethod()
    {
        if (try()) {
            // Do some work
            release();  // Do this--or risk being locked out
        } else {
            // Note that work wasn't done or try again
        }
    }
};