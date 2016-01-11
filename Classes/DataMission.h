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
	CC_SYNTHESIZE(int, __type, Type);//类型
	CC_SYNTHESIZE_RETAIN(CCString*, __title, Title);//标题
	CC_SYNTHESIZE_RETAIN(CCString*, __content, Content);//内容
	CC_SYNTHESIZE_RETAIN(CCString*, __mission, Mission);//任务
	CC_SYNTHESIZE(double, __target, Target);//目标
	CC_SYNTHESIZE(int, __reward, Reward);//奖励
};

#endif  //__DATA_MISSION_H__