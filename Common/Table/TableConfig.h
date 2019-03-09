/*
 * author: lhq
 * date  : 2017.9.2
 * bref	 : table config
 */

#ifndef	_TABLE_CONFIG_H
#define	_TABLE_CONFIG_H


class	TableConfig
{
public:
	TableConfig();
	~TableConfig();
public:
	void		Test();
private:
};

extern TableConfig	g_TableConfig;


#ifndef	TABLE_CONFIG
#define	TABLE_CONFIG	g_TableConfig
#endif

#endif
