#ifndef __SCENE_MAIN_H__
#define __SCENE_MAIN_H__

#include "cocos2d.h"
USING_NS_CC;

static const char RES_number_style_1[] = "fonts/atlas/number_style_1.png";
static const char RES_number_style_2[] = "fonts/atlas/number_style_2.png";
static const char RES_btn_back_1_0[] = "images/btn_back_1_0.png";
static const char RES_btn_back_1_1[] = "images/btn_back_1_1.png";

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
	//物品菜单项
	void menuGoodsCallback(CCObject* pSender);
	//打工菜单项
	void menuWorkCallback(CCObject* pSender);
	//休息菜单项
	void menuRestCallback(CCObject* pSender);
};

#endif // __SCENE_MAIN_H__
