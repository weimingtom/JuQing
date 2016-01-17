#ifndef __LAYER_REST_H__
#define __LAYER_REST_H__

#include "cocos2d.h"
#include "Topwo.h"
USING_NS_CC;

static const char RES_add_physical[] = "images/add_physical.png";
static const char RES_LayerRest_rest_1_0[] = "images/LayerRest_rest_1_0.png";
static const char RES_LayerRest_rest_1_1[] = "images/LayerRest_rest_1_1.png";
static const char RES_LayerRest_rest_2_0[] = "images/LayerRest_rest_2_0.png";
static const char RES_LayerRest_rest_2_1[] = "images/LayerRest_rest_2_1.png";
static const char RES_LayerRest_rest_3_0[] = "images/LayerRest_rest_3_0.png";
static const char RES_LayerRest_rest_3_1[] = "images/LayerRest_rest_3_1.png";

class LayerRest : public cocos2d::CCLayer
{
public:
	LayerRest();
	~LayerRest();
	virtual bool init();
	CREATE_FUNC(LayerRest);

	//≥ı ºªØUI
	bool initUI();
	virtual void registerWithTouchDispatcher() override;

	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent) override;
	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent) override;
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent) override;
	virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent) override;

	void menuCallbackClose(CCObject *pSender);
	void menuCallbackRest(CCObject *pSender);
	void rest(CCObject *pSender);
private:
	CCMenuItemSprite *__item_rest1;
	CCMenuItemSprite *__item_rest2;
	CCMenuItemSprite *__item_rest3;

	CCLabelAtlas *__la_add_physical_1;
	CCLabelAtlas *__la_add_physical_2;
	CCLabelAtlas *__la_add_physical_3;
};

#endif
