/*
* author: lhq
* date  : 2018.8.13
* bref	 : gdbase
*/

#ifndef		_GD_BASE_H
#define		_GD_BASE_H


struct GDTest
{
	int  MemPai;
	int  Level;

	GDTest(){ CleanUp();}
	void CleanUp()
	{
		MemPai = -1;
		Level  = -1;
	}
};



#endif
