#ifndef __DATA_NPC_H__
#define __DATA_NPC_H__
#include "cocos2d.h"

USING_NS_CC;

class DataNpc : public CCObject
{
public:
	DataNpc();
	virtual ~DataNpc();
	bool init();
	CREATE_FUNC(DataNpc);

private:
	CC_SYNTHESIZE(int, __id, Id);//Id
	CC_SYNTHESIZE_RETAIN(CCString*, __name, Name);//����
	CC_SYNTHESIZE_RETAIN(CCString*, __des, Des);//����
	CC_SYNTHESIZE(int, __favor_max, FavorMax);//�ܺøж�
	CC_SYNTHESIZE(int, __favor_cur, FavorCur);//��ǰ�øж�
};

#endif  //__DATA_NPC_H__