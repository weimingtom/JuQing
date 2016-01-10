#ifndef __SCENE_ACTION_H__
#define __SCENE_ACTION_H__

#include "cocos2d.h"
USING_NS_CC;

class SceneAction : public cocos2d::CCLayer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();

	// implement the "static node()" method manually
	CREATE_FUNC(SceneAction);

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* creatScene();

	//初始化UI
	bool initUI();

	//新的开始
	void menuNewCallback(CCObject* pSender);
	//旧的回忆
	void menuOldCallback(CCObject* pSender);
	//设置
	void menuSetCallback(CCObject* pSender);
	//帮助
	void menuHelpCallback(CCObject* pSender);
	//关于
	void menuAboutCallback(CCObject* pSender);
    //退出
	void menuCloseCallback(CCObject* pSender);

	//对话结束回调
	void callbackDialogOver();
};

#endif // __SCENE_ACTION_H__
