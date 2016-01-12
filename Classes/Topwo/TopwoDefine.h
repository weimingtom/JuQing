#ifndef __TOPWO_DEFINE_H__
#define __TOPWO_DEFINE_H__
#include "cocos2d.h"
USING_NS_CC;

#define NS_TOPWO_BEGIN                     namespace yieyo{
#define NS_TOPWO_END                       }
#define USING_NS_TOPWO                     using namespace yieyo

const double PI = 3.1415;
static const unsigned char BYTE_ORDER_MARK_UTF8_1 = 0xefU;
static const unsigned char BYTE_ORDER_MARK_UTF8_2 = 0xbbU;
static const unsigned char BYTE_ORDER_MARK_UTF8_3 = 0xbfU;


typedef int					twint;
typedef short				twshort;
typedef long				twlong;
typedef char				twchar;
typedef float               twfloat;
typedef bool				twbool;
typedef unsigned char       twbyte;
typedef unsigned short      twword;
typedef unsigned int		twuint;
typedef unsigned long       twdword;

#define TOPWO_CREATE_FUNC(__TYPE__,__PARENT_TYPE__) \
static __TYPE__* create() \
{ \
	__TYPE__ *pRet = new __TYPE__(); \
	if (pRet && pRet->__PARENT_TYPE__::init() && pRet->init()) \
	{ \
		pRet->autorelease(); \
	} \
	else \
	{ \
		delete pRet; \
		pRet = NULL; \
	} \
	return pRet; \
}

#endif  //__TOPWO_DEFINE_H__