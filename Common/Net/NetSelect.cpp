#include "NetSelect.h"


NetSelect::NetSelect()
{
	CleanUp();
}

NetSelect::~NetSelect()
{


}

void	NetSelect::Init()
{
	m_WorkThread.AddThread(this,&NetSelect::WorkThread);
}

void	NetSelect::Start()
{
	m_WorkThread.Start();
}

void	NetSelect::CleanUp()
{
	FD_ZERO(&m_Exception);
	FD_ZERO(&m_Read);
	FD_ZERO(&m_Write);
}

int		NetSelect::WorkThread(ThreadInfo& info)
{
	static int counter = 0;
	if(counter<5)
	{
		cout<<"thread test"<<endl;
		counter++;
	}
	return RET_SUCCESS;
}

void	NetSelect::HandleException()
{

}


void	NetSelect::HandleInput()
{

}

void	NetSelect::HandleOutPut()
{

}
