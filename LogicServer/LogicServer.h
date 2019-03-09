/*
 * author: lhq
 * date  : 2017.4.3
 * bref  : LogicServer 
 */

#ifndef		_LOGIC_SERVER_H
#define		_LOGIC_SERVER_H

#include "Common.h"
#include "Base/Module.h"
#include "PacketDispatcher.h"

class	LogicServer:public Module
{
public:
	LogicServer(){}
	~LogicServer(){}

	void				PreInit();
	void				Init();
	void				Start();
	void				Stop();
	void				CleanUp();
	void				HandleCmd();
public:
	PacketDispatcher&	 GetPacketDispatcher() { return m_PacketDispatcher; }
private:
	void				Test();
private:
	ModuleContainer		m_ModuleContainer;
	PacketDispatcher	m_PacketDispatcher;
};

extern LogicServer	g_LogicServer;

#ifndef		PACKET_DISPATCHER
#define		PACKET_DISPATCHER		g_LogicServer.GetPacketDispatcher()
#endif

#endif

