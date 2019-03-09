/*
 * author: lhq
 * date  : 2017.8.31
 * bref  : window  definition
 */

#ifndef		_WIN_H
#define		_WIN_H

#include <stdarg.h>
#include <time.h>

#include <WinSock2.h>
#include <Windows.h>
#include <process.h>

#pragma comment(lib,"ws2_32.lib")

#ifdef USE_PROTOBUF
	/**************************************************
	MS VC++ 15.0 _MSC_VER = 1910(VS2017)
	MS VC++ 14.0 _MSC_VER = 1900(VS2015)
	MS VC++ 12.0 _MSC_VER = 1800(VS2013)
	MS VC++ 11.0 _MSC_VER = 1700(VS2012)
	MS VC++ 10.0 _MSC_VER = 1600(VS2010)
	MS VC++ 9.0 _MSC_VER = 1500(VS2008)
	MS VC++ 8.0 _MSC_VER = 1400(VS2005)
	MS VC++ 7.1 _MSC_VER = 1310(VS2003)
	**************************************************/
#ifdef _DEBUG
	#if (_MSC_VER >= 1910 )
		#pragma comment(lib,"libprotobuf_vs2017_debug.lib")
	#elif (_MSC_VER >= 1800)
		#pragma comment(lib,"libprotobuf_vs2013_debug.lib")
	#elif (_MSC_VER >= 1500)
		#pragma comment(lib,"libprotobuf_debug.lib")
	#else
		#pragma comment(lib,"libprotobuf_debug.lib")
	#endif
#else
	#if (_MSC_VER >= 1910 )
		#pragma comment(lib,"libprotobuf_vs2017_release.lib")
	#elif (_MSC_VER >= 1800)
		#pragma comment(lib,"libprotobuf_vs2013_release.lib")
	#elif (_MSC_VER >= 1500)
		#pragma comment(lib,"libprotobuf_release.lib")
	#else
		#pragma comment(lib,"libprotobuf_release.lib")
	#endif
#endif


#endif

#ifdef USE_LIBUV
	#pragma comment(lib,"Iphlpapi.lib")
	#pragma comment(lib,"psapi.lib")
	#pragma comment(lib,"userenv.lib")

#ifdef _DEBUG
	#if (_MSC_VER >= 1910 )
		#pragma comment(lib,"libuv_vs2017_debug.lib")
	#elif (_MSC_VER >= 1800)
		#pragma comment(lib,"libuv.lib")
	#elif (_MSC_VER >= 1500)
		#pragma comment(lib,"libuv.lib")
	#else
		#pragma comment(lib,"libuv.lib")
	#endif
#else
	#if (_MSC_VER >= 1910 )
		#pragma comment(lib,"libuv_vs2017_release.lib")
	#elif (_MSC_VER >= 1800)
		#pragma comment(lib,"libuv.lib")
	#elif (_MSC_VER >= 1500)
		#pragma comment(lib,"libuv.lib")
	#else
		#pragma comment(lib,"libuv.lib")
	#endif
#endif
#endif // USE_LIBUV

#ifdef USE_MYSQL
	#pragma comment(lib,"libmysql.lib")
#endif

#ifdef USE_REDIS
#include "windows/hiredis.h"
#define NO_QFORKIMPL
#ifdef _DEBUG
	#pragma comment(lib,"hiredis_debug.lib")
	#pragma comment(lib,"Win32_Interop_debug.lib")
#else
	#pragma comment(lib,"hiredis_release.lib")
	#pragma comment(lib,"Win32_Interop_release.lib")
#endif

#endif


typedef		int					key_t;
typedef		HANDLE				TID;
typedef		__int64				INT64;


#define		THREAD_API			UINT WINAPI
#define		TLS					__declspec(thread)

//
class	GameLock
{
public:
	GameLock(){InitializeCriticalSection(&m_Lock);};
	~GameLock(){DeleteCriticalSection(&m_Lock);};
	void	Lock(){EnterCriticalSection(&m_Lock);};
	void    UnLock(){LeaveCriticalSection(&m_Lock);};
private:
	CRITICAL_SECTION		m_Lock;
};

#endif
