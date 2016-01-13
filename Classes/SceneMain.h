#ifndef __SCENE_MAIN_H__
#define __SCENE_MAIN_H__

#include "cocos2d.h"
USING_NS_CC;

class SceneMain : public cocos2d::CCLayer
{
public:
	virtual bool init();
	CREATE_FUNC(SceneMain);
    static cocos2d::CCScene* creatScene();

	//初始化UI
	bool initUI();
    
    //返回菜单项
	void menuBackCallback(CCObject* pSender);
	//任务菜单项
	void menuMissionCallback(CCObject* pSender);
	//锻炼菜单项
	void menuExerciseCallback(CCObject* pSender);
};

#endif // __SCENE_MAIN_H__
