/*
 *  autor: lhq
 *  date : 2016.11.5
 *  state: thread  
 */
#ifndef _THREAD_H_
#define _THREAD_H_

#include "Common.h"
#include "SystemApi.h"

#ifndef INVALID_ID
#define INVALID_ID -1
#endif


#ifndef IS_INVALID_ID
#define IS_INVALID_ID(val)  val==INVALID_ID?true:false
#endif

struct	ThreadInfo
{
	void*	 ContainerClass;
	void*    ThreadBoxFunc;
	BYTE	 ThreadIdx;
	int      TestArg1;
	ThreadInfo(){CleanUp();}
	void	CleanUp()
	{
		ContainerClass=NULL;
		ThreadBoxFunc = NULL;
		ThreadIdx = INVALID_ID;
		TestArg1=INVALID_ID;
	}
};

enum	THREAD_LOCAL_STORAGE_TYPE
{
	TLS_THREAD,
	TLS_NUM,
};

class	ThreadVal
{
public:

	static void*&   Current(THREAD_LOCAL_STORAGE_TYPE  type)
	{
		static TLS	void*  _ThreadVal[TLS_NUM]={NULL};
		return _ThreadVal[type];
	}

	template<typename DATA_T>
	static DATA_T*	GetThreadVal(THREAD_LOCAL_STORAGE_TYPE  type  )
	{
		return ((DATA_T*)Current(type));
	}

	template<typename DATA_T>
	static void	SetThreadVal(THREAD_LOCAL_STORAGE_TYPE  type,DATA_T* val)
	{
		ThreadVal::Current(type)=val;
	}

	static ThreadVal&  GetSingleton()
	{
		static ThreadVal _Ins;
		return _Ins;
	}
};

#ifndef THREAD_VAL
#define THREAD_VAL ThreadVal::GetSingleton()
#endif

#define		CURRENT_THREAD		  THREAD_VAL.GetThreadVal<ThreadInfo>(TLS_THREAD)
#define		SET_THREAD_VAL(data)  THREAD_VAL.SetThreadVal<ThreadInfo>(TLS_THREAD,data)

template<typename ContainerClass,const int ThreadNum=1>
class	ThreadBox
{
public:
	typedef	int (ContainerClass::*THREAD_FUNC)(ThreadInfo&);

	ThreadBox(){CleanUp();};
	~ThreadBox(){};

	void			CleanUp()
	{
		for(int i=0;i<ThreadNum;i++)
		{
			m_ThreadInfo[i].CleanUp();
		}
		m_ThreadName.clear();
	}

	
	template<typename MyClass,typename FUNC>
	void			AddThread(MyClass* cur_class,FUNC func,int thread_idx = 0)
	{
		if (thread_idx>= ThreadNum || cur_class == NULL || func == NULL)
		{
			return;
		}

		m_ThreadFunc[thread_idx] = func;
		m_ThreadInfo[thread_idx].ContainerClass=cur_class;
		m_ThreadInfo[thread_idx].ThreadIdx = thread_idx;
		m_ThreadInfo[thread_idx].ThreadBoxFunc=this;
	}
	

	
	BOOL			Start()
	{
		
		for(int i=0;i<ThreadNum;i++)
		{
#ifdef	_WINDOWS
			if (_beginthreadex(NULL,0,&ThreadBox::MainThread,&m_ThreadInfo[i],0,NULL) == 0 )
			{
				//TODO log
				PRINT_MSG(SystemApi::GetSystemErrorString());
				return false;
			}
#else
			pthread_t th;
			int ret = pthread_create(&th,NULL,&ThreadBox::MainThread,&m_ThreadInfo[i]); 
			if( ret != 0  )
			{
				PRINT_MSG(SystemApi::GetSystemErrorString());
				return false;
			}
#endif
		}

		return true;
		
	}
	


	
	static  THREAD_API MainThread(void* arg) 
	{
		ThreadInfo* cur_thread = (ThreadInfo*)arg;
		if (NULL == cur_thread)
		{
			return 0;
		}

		ThreadBox* thread_box = (ThreadBox*)cur_thread->ThreadBoxFunc;
		if (NULL == thread_box)
		{
			return 0;
		}

		ContainerClass* cur_class = (ContainerClass*)cur_thread->ContainerClass;
		THREAD_FUNC func = thread_box->m_ThreadFunc[cur_thread->ThreadIdx];
		if (cur_class == NULL )
		{
			return 0;
		}

		SET_THREAD_VAL(cur_thread);
		while(1)
		{
			SystemApi::SystemSleep(0);
			(cur_class->*func)( *cur_thread);
		}

		return 0;
	}

private:
	ThreadInfo				m_ThreadInfo[ThreadNum];
	THREAD_FUNC				m_ThreadFunc[ThreadNum];
	string					m_ThreadName;
};

#endif
