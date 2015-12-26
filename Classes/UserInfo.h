#ifndef __USER_INFO_H__
#define __USER_INFO_H__
#include "cocos2d.h"
#include "NpcData.h"

USING_NS_CC;

class UserInfo : public CCObject
{
public:
	UserInfo();
	virtual ~UserInfo();
	bool init();
	CREATE_FUNC(UserInfo);

	void addNpcDataToArray(NpcData* npc_data);
	NpcData* getNpcDataFromArray(int id);

private:
	CC_SYNTHESIZE_READONLY(CCArray*, __arr_npc_data, ArrOfNpcData);//npcµÄÊý¾Ý
};

#endif  //__USER_INFO_H__