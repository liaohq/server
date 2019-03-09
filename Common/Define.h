/*
 * author: lhq
 * date	 : 2017.4.3
 * bref  : general definition
 */

#ifndef		_DEFINE_H
#define		_DEFINE_H


enum	RET_TYPE
{
	RET_SUCCESS = 0,
	RET_FAIL	= 1,
};


#ifndef	INVALID_ID
#define INVALID_ID -1
#endif

#ifndef	IS_INVALID_ID
#define	IS_INVALID_ID(val)  (val==INVALID_ID?true:false)
#endif

#define IS_VALID(val)	!IS_INVALID_ID(val)

#define IS_NULL(val)	val==NULL?true:false

//
typedef	 unsigned int	UINT;
typedef	 unsigned int	TIME_T;
typedef	 unsigned char  BYTE;
typedef	 int			BOOL;


//
#define  MAX_BYTE		0xff
#define  MAX_SHORT		32767
#define	 MAX_USHORT		0xffff
#define	 MAX_INT		2147483647
#define  MAX_UINT		0xffffffff

#define  INT64_TO_BYTE(val)			((BYTE)(val&0xFF))
#define  INT64_TO_USHOR(val)		((unsigned short)(val&0xFFFF))


#ifndef NULL
#ifdef __cplusplus
   #define NULL 0
#else
    #define NULL ((void *)0)
#endif
#endif

#define DLL_EXPORT __declspec(dllexport)

#define	 DECLARE_VAR(type,name)			void   Set##name(type val) \
												{ m_##name = val;}   \
										type   Get##name(){return m_##name;}

#define PRINT_MSG(msg)		std::cout<<msg<<std::endl;

#define	BETWEEN(x,min_val,max_val)	( x<min_val?false:(x<=max_val?true:false) )
#define	SAFE_DELETE(ptr)	if(ptr){delete ptr;}
#define SAFE_MEMSET(src,dest,size)	 memset(src,dest,size)

#endif
