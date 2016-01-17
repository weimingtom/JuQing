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

	//��ʼ��UI
	bool initUI();
    
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
