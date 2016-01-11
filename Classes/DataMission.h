#ifndef __DATA_MISSION_H__
#define __DATA_MISSION_H__
#include "cocos2d.h"

USING_NS_CC;

class DataMission : public CCObject
{
public:
	DataMission();
	virtual ~DataMission();
	bool init();
	CREATE_FUNC(DataMission);

private:
	CC_SYNTHESIZE(int, __id, Id);//Id
	CC_SYNTHESIZE(int, __type, Type);//����
	CC_SYNTHESIZE_RETAIN(CCString*, __title, Title);//����
	CC_SYNTHESIZE_RETAIN(CCString*, __content, Content);//����
	CC_SYNTHESIZE_RETAIN(CCString*, __mission, Mission);//����
	CC_SYNTHESIZE(double, __target, Target);//Ŀ��
	CC_SYNTHESIZE(int, __reward, Reward);//����
};

#endif  //__DATA_MISSION_H__