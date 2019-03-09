/*
 * author:	lhq
 * date	 ;  2017.4.22
 * bref	 :  time api
 */

#ifndef		_TIME_MANAGE_H
#define		_TIME_MANAGE_H


#include "Common.h"

using namespace std;

class TimeManage
{
public:
	TimeManage(){}
	~TimeManage(){}

	static	TimeManage&	GetSingleton()
	{
		static TimeManage	Ins;
		return Ins;
	}

public:
	string			GetCurrentTimeStr();
	time_t			GetCurrentTime();
	int				GetTime();
	int				GetTick();
private:
	
};


#ifndef		TIME_API
#define		TIME_API   TimeManage::GetSingleton()
#endif


#endif
