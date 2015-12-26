#ifndef __NPC_DATA_H__
#define __NPC_DATA_H__
#include "cocos2d.h"

USING_NS_CC;

class NpcData : public CCObject
{
public:
	NpcData();
	virtual ~NpcData();
	bool init();
	CREATE_FUNC(NpcData);

private:
	CC_SYNTHESIZE(int, __id, Id);//Id
	CC_SYNTHESIZE(const char*, __name, Name);//名字
	CC_SYNTHESIZE(const char*, __des, Des);//描述
	CC_SYNTHESIZE(int, __favor_max, FavorMax);//总好感度
	CC_SYNTHESIZE(int, __favor_cur, FavorCur);//当前好感度
};

#endif  //__NPC_DATA_H__