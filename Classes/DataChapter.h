#ifndef __DATA_CHAPTER_H__
#define __DATA_CHAPTER_H__
#include "cocos2d.h"

USING_NS_CC;

class DataChapter : public CCObject
{
public:
	DataChapter();
	virtual ~DataChapter();
	bool init();
	CREATE_FUNC(DataChapter);

private:
	CC_SYNTHESIZE(int, __id, Id);//Id
	CC_SYNTHESIZE(int, __begin_id, BeginId);//¿ªÊ¼ID
	CC_SYNTHESIZE(int, __end_id, EndId);//½áÊøID
};

#endif  //__DATA_CHAPTER_H__