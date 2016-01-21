#ifndef __SCENE_MAIN_H__
#define __SCENE_MAIN_H__

#include "cocos2d.h"
USING_NS_CC;

static const char RES_number_style_1[] = "fonts/atlas/number_style_1.png";
static const char RES_number_style_2[] = "fonts/atlas/number_style_2.png";
static const char RES_number_style_5[] = "fonts/atlas/number_style_5.png";
static const char RES_btn_back_1_0[] = "images/btn_back_1_0.png";
static const char RES_btn_back_1_1[] = "images/btn_back_1_1.png";
static const char RES_btn_gift_0[] = "images/btn_gift_0.png";
static const char RES_btn_gift_1[] = "images/btn_gift_1.png";
static const char RES_btn_express_0[] = "images/btn_express_0.png";
static const char RES_btn_express_1[] = "images/btn_express_1.png";
static const char RES_btn_mission_0[] = "images/btn_mission_0.png";
static const char RES_btn_mission_1[] = "images/btn_mission_1.png";
static const char RES_btn_exercise_0[] = "images/btn_exercise_0.png";
static const char RES_btn_exercise_1[] = "images/btn_exercise_1.png";
static const char RES_btn_goods_0[] = "images/btn_goods_0.png";
static const char RES_btn_goods_1[] = "images/btn_goods_1.png";
static const char RES_btn_work_0[] = "images/btn_work_0.png";
static const char RES_btn_work_1[] = "images/btn_work_1.png";
static const char RES_btn_rest_0[] = "images/btn_rest_0.png";
static const char RES_btn_rest_1[] = "images/btn_rest_1.png";
static const char RES_SceneMain_progress_favor_bg[] = "images/SceneMain_progress_favor_bg.png";
static const char RES_SceneMain_progress_favor[] = "images/SceneMain_progress_favor.png";

class SceneMain : public cocos2d::CCLayer
{
public:
	virtual bool init();
	CREATE_FUNC(SceneMain);
    static cocos2d::CCScene* creatScene();

	//初始化UI
	bool initUI();
	//更新自己
	void updateMe();
    
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
