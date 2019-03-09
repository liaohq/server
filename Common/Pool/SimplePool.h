/*
 * author: lhq
 * data	 : 2017.4.7
 * bref	 : simple memory pool 
 */

#include<set>

typedef	 unsigned char	BYTE;

template<typename DATA_T,const int MAX_SIZE>
class	SimplePool
{
public:
	SimplePool()
	{
		m_Pool = NULL;
		m_Active = NULL;
		m_Index = 0;
		m_IdleList.clear();
	}

	~SimplePool()
	{
		if(NULL == m_Pool)
		{
			return;
		}
		delete [] m_Pool;
		delete [] m_Active;
	}

public:
	void		Init(int init_size = MAX_SIZE )
	{
		if(init_size>MAX_SIZE)
		{
			init_size = MAX_SIZE;
		}

		m_Pool = new DATA_T[MAX_SIZE];
		m_Active = new BYTE[MAX_SIZE];

		for(int i=0;i<init_size;i++)
		{
			m_Active[i] = false;
		}
	}

private:
	DATA_T*		m_Pool;
	BYTE*		m_Active;
	int			m_Index;
	set<int>	m_IdleList;
};
