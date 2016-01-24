#ifndef __LAYER_GOODS_H__
#define __LAYER_GOODS_H__

#include "cocos2d.h"
#include "Topwo.h"
USING_NS_CC;

static const char RES_LayerGoods_title[] = "images/LayerGoods_title.png";
static const char RES_btn_buy_0[] = "images/btn_buy_0.png";
static const char RES_btn_buy_1[] = "images/btn_buy_1.png";
static const char RES_LayerGoods_tipo[] = "images/LayerGoods_tipo.png";
static const char RES_LayerGoods_meili[] = "images/LayerGoods_meili.png";
static const char RES_LayerGoods_zhili[] = "images/LayerGoods_zhili.png";
static const char RES_LayerGoods_eq[] = "images/LayerGoods_eq.png";
static const char RES_LayerGoods_ganxing[] = "images/LayerGoods_ganxing.png";

class LayerGoods : public cocos2d::CCLayer
{
public:
	LayerGoods();
	~LayerGoods();
	virtual bool init();
	CREATE_FUNC(LayerGoods);

	//初始化UI
	bool initUI();
	virtual void registerWithTouchDispatcher() override;

	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent) override;
	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent) override;
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent) override;
	virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent) override;

	void menuCallbackClose(CCObject* pSender);
	void menuCallbackBuy(CCObject* pSender);

	void hintCallbackWork(CCNode *node);

	void updateMe();

	int getGoodsLevel(int level);
	int getGoodsPrice(int level);
	int getGoodsBonus(int level);
private:
};

#endif // __LAYER_GOODS_H__
