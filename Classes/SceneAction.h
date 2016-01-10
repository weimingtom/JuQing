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

	//��ʼ��UI
	bool initUI();

	//�µĿ�ʼ
	void menuNewCallback(CCObject* pSender);
	//�ɵĻ���
	void menuOldCallback(CCObject* pSender);
	//����
	void menuSetCallback(CCObject* pSender);
	//����
	void menuHelpCallback(CCObject* pSender);
	//����
	void menuAboutCallback(CCObject* pSender);
    //�˳�
	void menuCloseCallback(CCObject* pSender);

	//�Ի������ص�
	void callbackDialogOver();
};

#endif // __SCENE_ACTION_H__
