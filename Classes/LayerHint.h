#ifndef __LAYER_HINT_H__
#define __LAYER_HINT_H__

#include "cocos2d.h"
#include "Topwo.h"
USING_NS_CC;

static const char RES_LayerHint_bg[] = "images/LayerHint_bg.png";
static const char RES_btn_confirm_0[] = "images/btn_confirm_0.png";
static const char RES_btn_confirm_1[] = "images/btn_confirm_1.png";
static const char RES_btn_cancel_0[] = "images/btn_cancel_0.png";
static const char RES_btn_cancel_1[] = "images/btn_cancel_1.png";

class LayerHint : public cocos2d::CCLayer
{
public:
	LayerHint();
	~LayerHint();
	CREATE_FUNC(LayerHint);
	virtual bool initWith(CCLabelTTF *content, int style, CCObject* target, SEL_CallFuncN callfun);
	static LayerHint* createWith(CCLabelTTF *content, int style, CCObject* target, SEL_CallFuncN callfun);

	//初始化UI
	bool initUIWith(CCLabelTTF *content, int style);
	virtual void registerWithTouchDispatcher() override;

	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent) override;
	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent) override;
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent) override;
	virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent) override;
private:
	void buttonCallBack(CCObject* pSender);
	CCObject* __callbackListener;
	SEL_CallFuncN __callbackfun;
};

#endif //__LAYER_HINT_H__
