/*
* author: lhq
* date  : 2017.9.13
* bref	 : net select
*/

#ifndef		_NET_SELECT_H
#define		_NET_SELECT_H

#include "Common.h"
#include "Base/Thread.h"

class NetSelect
{
public:
	NetSelect();
	~NetSelect();

public:
	void					Init();
	void					Start();
	void					CleanUp();
private:
	void					HandleException();
	void					HandleInput();
	void					HandleOutPut();

private:
	int						WorkThread(ThreadInfo&  info);
private:
	ThreadBox<NetSelect>	m_WorkThread;
	
    fd_set					m_Write;
	fd_set					m_Read;
	fd_set					m_Exception;

};



#endif
