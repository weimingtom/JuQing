#ifndef __USER_INFO_H__
#define __USER_INFO_H__
#include "cocos2d.h"
#include "DataNpc.h"
#include "DataChapter.h"

USING_NS_CC;

class UserInfo : public CCObject
{
public:
	UserInfo();
	virtual ~UserInfo();
	bool init();
	CREATE_FUNC(UserInfo);

	void addDataNpcToArray(DataNpc* npc_data);
	DataNpc* getDataNpcFromArray(int id);
	void addDataChapterToArray(DataChapter* npc_data);
	DataChapter* getDataChapterFromArray(int id);

private:
	CC_SYNTHESIZE_READONLY(CCArray*, __arr_data_npc, ArrOfDataNpc);//npc的数据
	CC_SYNTHESIZE_READONLY(CCArray*, __arr_data_chapter, ArrOfDataChapter);//章节的数据
};

#endif  //__USER_INFO_H__