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

	//��ʼ��UI
	bool initUI();
	//�����Լ�
	void updateMe();
    
    //���ز˵���
	void menuBackCallback(CCObject* pSender);
	//����˵���
	void menuMissionCallback(CCObject* pSender);
	//�����˵���
	void menuExerciseCallback(CCObject* pSender);
	//��Ʒ�˵���
	void menuGoodsCallback(CCObject* pSender);
	//�򹤲˵���
	void menuWorkCallback(CCObject* pSender);
	//��Ϣ�˵���
	void menuRestCallback(CCObject* pSender);
};

#endif // __SCENE_MAIN_H__
