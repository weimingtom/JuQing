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
	CC_SYNTHESIZE(const char*, __name, Name);//����
	CC_SYNTHESIZE(const char*, __des, Des);//����
	CC_SYNTHESIZE(int, __favor_max, FavorMax);//�ܺøж�
	CC_SYNTHESIZE(int, __favor_cur, FavorCur);//��ǰ�øж�
};

#endif  //__NPC_DATA_H__