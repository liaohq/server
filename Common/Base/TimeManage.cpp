#include"stdafx.h"
#include"TimeManage.h"


string	TimeManage::GetCurrentTimeStr()
{
	time_t  timer;

	time(&timer);
	struct tm*  cur_time = localtime(&timer);
	if( NULL == cur_time)
	{
		cout<<"GetCurrentTime err "<<endl;
		return "";
	}

	char buf[128]={0};
	sprintf(buf,"%04d-%02d-%02d %02d:%02d:%2d",cur_time->tm_year+1900,cur_time->tm_mon+1,cur_time->tm_mday,cur_time->tm_hour,cur_time->tm_min,cur_time->tm_sec);

	string time_str(buf);
	return time_str;
}

time_t		TimeManage::GetCurrentTime()
{
	time_t  timer;
	return time(&timer);
}

int		TimeManage::GetTime()
{
	//struct timeval tv;
	//struct timezone tz;

	//gettimeofday(&tv,&tz);


	//return tv.tv_sec;

	return INVALID_ID;
}

int		TimeManage::GetTick()
{
	//struct  timeval	tv;
	//gettimeofday(&tv,NULL);

	//return tv.tv_sec*1000+tv.tv_usec/1000;

	return INVALID_ID;
}
