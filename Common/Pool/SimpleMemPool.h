/*
	author : lhq
	date   : 2017.5.1
	bref   : simple memory pool 
*/

#ifndef		_SIMPLE_MEM_POOL_H
#define		_SIMPLE_MEM_POOL_H

#include<vector>

template<typename T,size_t BlockSize=32>
class	SimpleMemPool
{
public:
	typedef T		  value_type;
	typedef size_t    size_type;
	typedef ptrdiff_t difference_type;
	typedef T*		  pointer;
	typedef const T*  const_pointer;
	typedef T&		  reference;
	typedef const T&  const_reference;

	SimpleMemPool()
	{
		m_Pool = NULL;
		m_Index = 0;
		m_IdleIndex=0;
		m_Pool = new value_type[BlockSize];
	}

	~SimpleMemPool()
	{
		if (m_Pool)
		{
			delete[] m_Pool;
			m_Pool = NULL;
		}
	}
public:
	pointer	NewElement()
	{
		if ( m_IdleIndex>0)
		{
			pointer  elem= m_Idlelist[--m_IdleIndex];
			if (elem == NULL)
			{
				return NULL;
			}
			new (elem) value_type();

			return elem;
		}

		if (m_Index>=BlockSize)
		{//todo new memory 
			return NULL;
		}

		pointer elem = &m_Pool[m_Index];
		if (elem == NULL)
		{
			return NULL;
		}

		new (elem) value_type();
		m_Index++;
		
		return elem;
	}

	void			FreeElement(pointer  elem)
	{
		if ( elem == NULL )
		{
			return;
		}

		elem->~value_type();
		m_Idlelist[m_IdleIndex++]=elem;

	}
private:
	pointer			m_Pool;
	value_type*		m_Idlelist[BlockSize];
	size_t			m_Index;
	size_t			m_IdleIndex;
};

#endif