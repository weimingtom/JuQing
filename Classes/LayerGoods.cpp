#include "LayerGoods.h"
#include "LayerExercise.h"
#include "LayerMission.h"

LayerGoods::LayerGoods()
{

}
LayerGoods::~LayerGoods()
{
}
bool LayerGoods::init()
{
    // 1. super init first
    if (!CCLayer::init() )
    {
        return false;
	}

	initUI();

	setTouchEnabled(true);  //开启触摸响应

    return true;
}
void LayerGoods::registerWithTouchDispatcher()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, kCCMenuHandlerPriority, true);
}
//初始化UI
bool LayerGoods::initUI()
{
	CCPoint vo = CCDirector::sharedDirector()->getVisibleOrigin();
	CCSize vs = CCDirector::sharedDirector()->getVisibleSize();

	//背景
	CCScale9Sprite* sp_bg = CCScale9Sprite::create(RES_white_dialog);
	this->addChild(sp_bg);
	sp_bg->setContentSize(CCSizeMake(780.0f, 340.0f));
	CCSize size_sp_bg = sp_bg->getContentSize();
	sp_bg->setPosition(ccp(vs.width * 0.5f, vs.height * 0.5f));

	//标题
	CCSprite *sp_title = CCSprite::create(RES_LayerGoods_title);
	this->addChild(sp_title);
	CCSize size_sp_title = sp_title->getContentSize();
	sp_title->setPosition(ccp(vs.width * 0.5f, (vs.height + size_sp_bg.height) * 0.5f - size_sp_title.height * 0.8f));

	//关闭项
	CCMenuItemSprite *item_close = CCMenuItemSprite::create(
		CCSprite::create(RES_btn_close_1_0),
		CCSprite::create(RES_btn_close_1_0),
		this,
		menu_selector(LayerGoods::menuCallbackClose)
		);
	CCSize size_item_close = item_close->getContentSize();
	CCNode *node = item_close->getNormalImage();
	node->setAnchorPoint(ccp(0.5f, 0.5f));
	node->setPosition(ccp(size_item_close.width * 0.5f, size_item_close.height * 0.5f));
	node = item_close->getSelectedImage();
	node->setAnchorPoint(ccp(0.5f, 0.5f));
	node->setPosition(ccp(size_item_close.width * 0.5f, size_item_close.height * 0.5f));
	node->setScale(1.2f);
	item_close->setPosition(ccp((vs.width + size_sp_bg.width - size_item_close.width) * 0.5f, (vs.height + size_sp_bg.height - size_item_close.height) * 0.5f));

	//购买物品1
	CCSprite *sp_goods_1 = CCSprite::create(RES_LayerGoods_tipo);
	this->addChild(sp_goods_1);
	CCSize size_sp_goods_1 = sp_goods_1->getContentSize();
	sp_goods_1->setPosition(ccp(vs.width * 0.5f - size_sp_goods_1.width * 2.04f, vs.height * 0.43f));

	CCMenuItemSprite *item_buy_goods_1 = CCMenuItemSprite::create(
		CCSprite::create(RES_btn_buy_0),
		CCSprite::create(RES_btn_buy_1),
		this,
		menu_selector(LayerGoods::menuCallbackClose)
		);
	item_buy_goods_1->setPosition(ccp(vs.width * 0.5f - size_sp_goods_1.width * 2.04f, vs.height * 0.31f));

	//购买物品2
	CCSprite *sp_goods_2 = CCSprite::create(RES_LayerGoods_meili);
	this->addChild(sp_goods_2);
	sp_goods_2->setPosition(ccp(vs.width * 0.5f - size_sp_goods_1.width * 1.02f, vs.height * 0.43f));

	CCMenuItemSprite *item_buy_goods_2 = CCMenuItemSprite::create(
		CCSprite::create(RES_btn_buy_0),
		CCSprite::create(RES_btn_buy_1),
		this,
		menu_selector(LayerGoods::menuCallbackClose)
		);
	item_buy_goods_2->setPosition(ccp(vs.width * 0.5f - size_sp_goods_1.width * 1.02f, vs.height * 0.31f));

	//购买物品3
	CCSprite *sp_goods_3 = CCSprite::create(RES_LayerGoods_zhili);
	this->addChild(sp_goods_3);
	sp_goods_3->setPosition(ccp(vs.width * 0.5f, vs.height * 0.43f));

	CCMenuItemSprite *item_buy_goods_3 = CCMenuItemSprite::create(
		CCSprite::create(RES_btn_buy_0),
		CCSprite::create(RES_btn_buy_1),
		this,
		menu_selector(LayerGoods::menuCallbackClose)
		);
	item_buy_goods_3->setPosition(ccp(vs.width * 0.5f, vs.height * 0.31f));

	//购买物品4
	CCSprite *sp_goods_4 = CCSprite::create(RES_LayerGoods_eq);
	this->addChild(sp_goods_4);
	sp_goods_4->setPosition(ccp(vs.width * 0.5f + size_sp_goods_1.width * 1.02f, vs.height * 0.43f));

	CCMenuItemSprite *item_buy_goods_4 = CCMenuItemSprite::create(
		CCSprite::create(RES_btn_buy_0),
		CCSprite::create(RES_btn_buy_1),
		this,
		menu_selector(LayerGoods::menuCallbackClose)
		);
	item_buy_goods_4->setPosition(ccp(vs.width * 0.5f + size_sp_goods_1.width * 1.02f, vs.height * 0.31f));

	//购买物品5
	CCSprite *sp_goods_5 = CCSprite::create(RES_LayerGoods_ganxing);
	this->addChild(sp_goods_5);
	sp_goods_5->setPosition(ccp(vs.width * 0.5f + size_sp_goods_1.width * 2.04f, vs.height * 0.43f));

	CCMenuItemSprite *item_buy_goods_5 = CCMenuItemSprite::create(
		CCSprite::create(RES_btn_buy_0),
		CCSprite::create(RES_btn_buy_1),
		this,
		menu_selector(LayerGoods::menuCallbackClose)
		);
	item_buy_goods_5->setPosition(ccp(vs.width * 0.5f + size_sp_goods_1.width * 2.04f, vs.height * 0.31f));

	CCMenu *menu = CCMenu::create(item_close, item_buy_goods_1, item_buy_goods_2, item_buy_goods_3, item_buy_goods_4, item_buy_goods_5, NULL);
	this->addChild(menu);
	menu->setPosition(CCPointZero);

	return true;
}
bool LayerGoods::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	return true;
}
void LayerGoods::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
}
void LayerGoods::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
}
void LayerGoods::ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent)
{
}

void LayerGoods::menuCallbackClose(CCObject* pSender)
{
	this->removeFromParent();
}