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

	//≥ı ºªØUI
	bool initUI();
    
    // a selector callback
	void menuBackCallback(CCObject* pSender);

	void menuMissionCallback(CCObject* pSender);
};

#endif // __SCENE_MAIN_H__
