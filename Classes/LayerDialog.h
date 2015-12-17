#ifndef __LAYER_DIALOG_H__
#define __LAYER_DIALOG_H__

#include "cocos2d.h"
#include "Topwo.h"
USING_NS_CC;

class LayerDialog : public cocos2d::CCLayer
{
public:
	virtual bool init();
	CREATE_FUNC(LayerDialog);
	static LayerDialog* createWith(int start_id, int end_id);

	//��ʼ��UI
	bool initUI();

	virtual void onExit() override;

	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent) override;
	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent) override;
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent) override;
	virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent) override;
    
    //�ص�
	void menuCloseCallback(CCObject* pSender);
	void menuBeginCallback(CCObject* pSender);

	//����һ��Ի�
	void analyzeDialog(int index);
	//���ֽ����ص�
	void typedCallBack();
private:
	CCSprite* __bg;
	CCSprite* __vertical_drawing;
	CCLabelTTF* __name;
	TopwoTypeTTF* __dialog;
	bool __is_typed_all;
	int __start_id;
	int __end_id;
	int __current_id;
};

#endif // __SCENE_DIALOG_H__
