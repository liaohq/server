/*
 * author: lhq
 * date  : 2017.4.3
 * bref	 : sock
 */

#ifndef		_SOCKET_H
#define		_SOCKET_H



class	Socket
{
public:
	Socket();
	~Socket();

	void		CleanUp();
public:
    DECLARE_VAR(int,ContainerIdx);	

private:

	int			m_ContainerIdx;


};


#endif
