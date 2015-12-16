#ifndef __LAYER_DIALOG_H__
#define __LAYER_DIALOG_H__

#include "cocos2d.h"
USING_NS_CC;

class LayerDialog : public cocos2d::CCLayer
{
public:
	virtual bool init();
	CREATE_FUNC(LayerDialog);

	//≥ı ºªØUI
	bool initUI();

	virtual void onExit() override;

	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent) override;
	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent) override;
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent) override;
	virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent) override;
    
    // a selector callback
	void menuCloseCallback(CCObject* pSender);

	void menuBeginCallback(CCObject* pSender);

	void labelCallBack();
private:
	CCSprite* __bg;
	CCSprite* __bg_name;
	CCSprite* __bg_dialog;
	CCSprite* __vertical_drawing;
};

#endif // __SCENE_DIALOG_H__
