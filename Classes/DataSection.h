#ifndef __DATA_SECTION_H__
#define __DATA_SECTION_H__
#include "cocos2d.h"

USING_NS_CC;

class DataSection : public CCObject
{
public:
	DataSection();
	virtual ~DataSection();
	bool init();
	CREATE_FUNC(DataSection);

private:
	CC_SYNTHESIZE(int, __id, Id);//Id
	CC_SYNTHESIZE(int, __begin_id, BeginId);//开始ID
	CC_SYNTHESIZE(int, __end_id, EndId);//结束ID
};

#endif  //__DATA_SECTION_H__