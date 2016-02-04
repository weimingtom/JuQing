#ifndef __SCENE_ACTION_H__
#define __SCENE_ACTION_H__

#include "cocos2d.h"
USING_NS_CC;

static const char RES_SceneAction_bg[] = "images/SceneAction_bg.jpg";
static const char RES_SceneAction_new_0[] = "images/SceneAction_new_0.png";
static const char RES_SceneAction_new_1[] = "images/SceneAction_new_1.png";
static const char RES_SceneAction_old_0[] = "images/SceneAction_old_0.png";
static const char RES_SceneAction_old_1[] = "images/SceneAction_old_1.png";
static const char RES_SceneAction_end_0[] = "images/SceneAction_end_0.png";
static const char RES_SceneAction_end_1[] = "images/SceneAction_end_1.png";
static const char RES_btn_sound_on_0[] = "images/btn_sound_on_0.png";
static const char RES_btn_sound_on_1[] = "images/btn_sound_on_1.png";
static const char RES_btn_sound_off_0[] = "images/btn_sound_off_0.png";
static const char RES_btn_sound_off_1[] = "images/btn_sound_off_1.png";
static const char RES_SceneAction_logo[] = "images/SceneAction_logo.png";
static const char RES_SceneAction_decoration_1[] = "images/SceneAction_decoration_1.png";
static const char RES_SceneAction_decoration_2[] = "images/SceneAction_decoration_2.png";

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
	virtual void keyBackClicked() override;

	//新的开始
	void menuNewCallback(CCObject* pSender);
	//旧的回忆
	void menuOldCallback(CCObject* pSender);
    //退出
	void menuCloseCallback(CCObject* pSender);
	//设置
	void menuSetCallback(CCObject* pSender);
	//帮助
	void menuHelpCallback(CCObject* pSender);
	//关于
	void menuAboutCallback(CCObject* pSender);
	//重新开始
	void hintCallbackRestart(CCNode *node);
    //新的开始
    void newGame();

	//对话结束回调
	void callbackDialogOver();
};

#endif // __SCENE_ACTION_H__
