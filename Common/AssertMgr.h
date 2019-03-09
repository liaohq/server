/*
 *  autor: lhq
 *  date : 2017.6.1
 *  state: asset_mgr
 */
#ifndef _ASSERT_MGR_H
#define _ASSERT_MGR_H

#include "Common.h"
#include "HeadHelper.h"

typedef	 unsigned char  BYTE;
typedef	 unsigned int   UINT;

#ifndef TRUE_B
#define TRUE_B  1
#endif

#ifndef FALSE_B 
#define FALSE_B  0
#endif


typedef	void (*ASSERT_CB_FUNC)(char* msg);

struct	Assert
{
	static const int MAX_ASSERT_SIZE = 10000;


	static Assert&  GetSingleton()
	{
		static Assert  _Ins;
		return _Ins;
	}

	void	 Init(ASSERT_CB_FUNC func)
	{
		Func = func;
	}

	Assert(){ CleanUp();}
	void     CleanUp()
	{
		for(int i=0;i<MAX_ASSERT_SIZE;i++)
		{
			EnableList[i] = TRUE_B;
		}
	}

	bool	IsEnalbe(UINT assert_id)
	{
		return  EnableList[assert_id%MAX_ASSERT_SIZE] == TRUE_B;
	}

	void	SetEnable(UINT assert_id,BYTE  enable = FALSE_B)
	{
		EnableList[assert_id%MAX_ASSERT_SIZE] = enable;
	}

	void	DumpFunc(UINT assert_id,const char* file_name,long file_line,const char* func_name,const char* msg,...)
	{
		if (!file_name || !file_line || !func_name  || !msg )
		{
			return;
		}

#ifdef _DEBUG
		_ASSERTE(0);
#endif
		char  tmp_buf[1024]={0};				
		va_list ap;							
		va_start(ap,msg);					
		vsprintf( tmp_buf,msg,ap); 
		va_end(ap);							


		char buf[1024]={0};
		sprintf(buf,"Assert:\n Day:%s,Time:%s,FileName:%s,FileLine:%d,FuncName:%s,Msg:%s \n",__DATE__,__TIME__,file_name,file_line,func_name,tmp_buf);
		cout<<buf<<endl;

		if (Func)
		{
			Func(buf);
		}
	}

	BYTE			EnableList[MAX_ASSERT_SIZE];
	ASSERT_CB_FUNC  Func;

};

#ifndef ASSERT_MGR
#define ASSERT_MGR Assert::GetSingleton()
#endif


/*
#define	 GAME_ASSERT_MSG(x,msg,...)	  if( !(x) ) \
								 {\
									static UINT  assert_id = __COUNTER__; \
									if(ASSERT_MGR.IsEnalbe(assert_id))     \
									{\
										ASSERT_MGR.SetEnable(assert_id);	\
										ASSERT_MGR.DumpFunc(assert_id,__FILE__,__LINE__,__FUNCTION__,msg,##__VA_ARGS__); \
									}\
								  }
 */

#define	 GAME_ASSERT_MSG(x,msg,...)	  if( !(x) ) \
								 {\
									static int  enable = 1; \
									if(enable)     \
									{\
										enable=0;	\
										ASSERT_MGR.DumpFunc(__COUNTER__,__FILE__,__LINE__,__FUNCTION__,msg,##__VA_ARGS__); \
									}\
								  }

static void  __show__(const char* szTemp)
{
	//保存日志 TODO create file
	//FILE* f = fopen("./Log/assert.log", "a");
	//fwrite(szTemp, 1, strlen(szTemp), f);
	//fwrite("\r\n", 1, 2, f);
	//fclose(f);

#if defined(_WINDOWS)
	::MessageBoxA(NULL, szTemp, "异常信息", MB_OK);
#endif
	printf("Assert:%s \n", szTemp);
}

static void __assert__(const char * file, UINT line, const char * func, const char * expr)
{
	char szTemp[1024] = { 0 };

	sprintf(szTemp, "Time:%s,FileName:%s,Line:%d,Function:%s \n", __TIME__,file, line, func);

	__show__(szTemp);
}

#ifdef	_WINDOWS
	#define GAME_ASSERT(expr) ((VOID)((expr)?0:(__assert__(__FILE__,__LINE__,__FUNCTION__,#expr),0)))
#else
	#define GAME_ASSERT(expr) {if(!(expr)){__assert__(__FILE__,__LINE__,__PRETTY_FUNCTION__,#expr);}}
#endif

#include "FootHelper.h"

#endif
