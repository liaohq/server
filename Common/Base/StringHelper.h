/*
 *  autor: lhq
 *  date : 2017.10.17
 *  state: string helper
 */

#ifndef	_STRING_HELPER_H
#define	_STRING_HELPER_H

#include<stdlib.h>
#include<vector>
#include "AssertMgr.h"

using namespace std;

class	StringHelper
{
public:
	inline	static int		ToInt(const char* arg);
	inline  static int		Replace(string& src,const string& old_str,const string& new_str);
	inline  static const string		ToString(const char* msg,...);
	inline	static void		Split(const string& src,const string& match,vector<string>& out_list);
};

int	StringHelper::ToInt(const char* arg)
{
	try
	{
		if(arg == NULL ){return 0;}
		return atoi(arg);
	}
	catch(...)
	{
		return 0;
	}
}

int StringHelper::Replace(string& src,const string& old_str,const string& new_str)
{
	int count = 0;
	size_t old_len = old_str.length();
	size_t new_len = new_str.length();
	size_t pos = 0;
	while( (pos=src.find(old_str,pos))!= string::npos)
	{
		src.replace(pos,old_len,new_str);
		pos+=new_len;
		count++;
	}
	return count;
}

const string	 StringHelper::ToString(const char* msg,...)
{
	if (msg == NULL)
	{
		return NULL;
	}

	const int MAX_BUF_SIZE=1024;
	char	tmp_buf[MAX_BUF_SIZE] = { 0 };

	va_list  argptr;
	va_start(argptr, msg);
	//int nchars=vsprintf(tmp_buf, msg, argptr);
	int nchars=vsnprintf(tmp_buf,MAX_BUF_SIZE,msg,argptr);
	va_end(argptr);
	if (nchars == -1 || nchars >sizeof(tmp_buf) )
	{
		GAME_ASSERT(FALSE);
		return NULL;
	}

	tmp_buf[MAX_BUF_SIZE]='\0';
	return string(tmp_buf);
}

void	StringHelper::Split(const string& src,const string& match,vector<string>& out_list)
{
	if( src.empty() || match.empty() )
	{
		return;
	}

	string::size_type pos1=0,pos2=0;
	pos2 = src.find(match);
	
	while( string::npos != pos2)
	{
		out_list.push_back(src.substr(pos1,pos2-pos1));
		pos1 = pos2+1;
		pos2 = src.find(match,pos1);
	}

	if(pos1 != src.length())
	{
		out_list.push_back(src.substr(pos1));
	}

}

#endif
