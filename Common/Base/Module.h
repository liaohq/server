/*
 * author: lhq
 * date  : 2017.4.3
 * bref  : module base
 */
 
#ifndef		_MODULE_H
#define		_MODULE_H

#include<set>

class	ModuleBase
{
public:
	ModuleBase(){}
	~ModuleBase(){}
	
	virtual		void	PreInit()=0;
	virtual		void	Init()=0;
	virtual		void	Start()=0;
	virtual		void	Stop()=0;
	virtual		void	CleanUp()=0;
};


class	Module:public ModuleBase
{
public:
	Module(){}
	~Module(){}

	void			SetName(const char* name){m_Name = name;}
	const string&	GetName(){return m_Name;}
private:
	string		m_Name;
};


class  ModuleContainer
{
public:
	ModuleContainer(){}
	~ModuleContainer(){}

	void		RegisterModule(Module* module,const char* name)
	{
		if( NULL == module || NULL == name )
		{
			return;
		}

		module->SetName(name);
		
		m_ModuleList.insert(module);
	}

	void		PreInit()
	{
		set<Module*>::const_iterator	it=m_ModuleList.begin();
		for(;it!=m_ModuleList.end();++it)
		{
			Module* cur_module = *it;
			if(NULL == cur_module)
			{
				continue;
			}
			cur_module->PreInit();
		}
	}

	void		Init()
	{
		set<Module*>::const_iterator	it=m_ModuleList.begin();
		for(;it!=m_ModuleList.end();++it)
		{
			Module* cur_module = *it;
			if(NULL == cur_module)
			{
				continue;
			}
			cur_module->Init();
		}
	}

	void		Start()
	{
		set<Module*>::const_iterator	it=m_ModuleList.begin();
		for(;it!=m_ModuleList.end();++it)
		{
			Module* cur_module = *it;
			if(NULL == cur_module)
			{
				continue;
			}
			cur_module->Start();
		}
	}
	void		Stop()
	{
		set<Module*>::const_iterator	it=m_ModuleList.begin();
		for(;it!=m_ModuleList.end();++it)
		{
			Module* cur_module = *it;
			if(NULL == cur_module)
			{
				continue;
			}
			cur_module->Stop();
		}
	}
	void		CleanUp()
	{
		set<Module*>::const_iterator	it=m_ModuleList.begin();
		for(;it!=m_ModuleList.end();++it)
		{
			Module* cur_module = *it;
			if(NULL == cur_module)
			{
				continue;
			}
			cur_module->CleanUp();
		}
	}

private:
	set<Module*>	m_ModuleList;
};

#endif
