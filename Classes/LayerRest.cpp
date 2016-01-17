#include "LayerRest.h"
#include "LayerMission.h"
#include "LayerExercise.h"
#include "SceneMain.h"
#include "LayerProgress.h"

LayerRest::LayerRest()
{

}
LayerRest::~LayerRest()
{
}
bool LayerRest::init()
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
void LayerRest::registerWithTouchDispatcher()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, kCCMenuHandlerPriority, true);
}
//初始化UI
bool LayerRest::initUI()
{
	CCPoint vo = CCDirector::sharedDirector()->getVisibleOrigin();
	CCSize vs = CCDirector::sharedDirector()->getVisibleSize();

	CCSprite* sp_bg = CCSprite::create(RES_white_dialog);
	this->addChild(sp_bg);
	CCSize size_sp_bg = sp_bg->getContentSize();
	sp_bg->setPosition(ccp(vs.width * 0.5f, vs.height * 0.5f));

	CCMenuItemSprite *item_close = CCMenuItemSprite::create(
		CCSprite::create(RES_btn_close_1_0),
		CCSprite::create(RES_btn_close_1_0),
		this,
		menu_selector(LayerRest::menuCallbackClose)
		);
	CCSize size_item_close = item_close->getContentSize();
	CCNode *node = item_close->getNormalImage();
	node->setAnchorPoint(ccp(0.5f, 0.5f));
	node->setPosition(ccp(size_item_close.width * 0.5f, size_item_close.height * 0.5f));
	node = item_close->getSelectedImage();
	node->setAnchorPoint(ccp(0.5f, 0.5f));
	node->setPosition(ccp(size_item_close.width * 0.5f, size_item_close.height * 0.5f));
	node->setScale(1.2f);
	item_close->setPosition((vs.width + size_sp_bg.width - size_item_close.width) * 0.5f, (vs.height + size_sp_bg.height - size_item_close.height) * 0.5f);
	
	__item_rest1 = CCMenuItemSprite::create(
		CCSprite::create(RES_LayerRest_rest_1_0),
		CCSprite::create(RES_LayerRest_rest_1_1),
		this,
		menu_selector(LayerRest::menuCallbackRest)
		);
	CCSize size_item_rest1 = __item_rest1->getContentSize();
	__item_rest1->setPosition(vs.width * 0.54f, vs.height * 0.5f + size_item_rest1.height * 1.6f);

	CCSprite* sp_add_physical_1 = CCSprite::create(RES_add_physical);
	this->addChild(sp_add_physical_1);
	CCSize size_sp_add_physical_1 = sp_add_physical_1->getContentSize();
	sp_add_physical_1->setPosition(ccp(vs.width * 0.29f, vs.height * 0.5f + size_item_rest1.height * 1.6f));

	__la_add_physical_1 = CCLabelAtlas::create("50", RES_number_style_1, 20, 20, '0');
	sp_add_physical_1->addChild(__la_add_physical_1);
	__la_add_physical_1->setAnchorPoint(ccp(0, 0.5f));
	__la_add_physical_1->setPosition(ccp(size_sp_add_physical_1.width, size_sp_add_physical_1.height * 0.5f));

	__item_rest2 = CCMenuItemSprite::create(
		CCSprite::create(RES_LayerRest_rest_2_0),
		CCSprite::create(RES_LayerRest_rest_2_1),
		this,
		menu_selector(LayerRest::menuCallbackRest)
		);
	__item_rest2->setPosition(vs.width * 0.54f, vs.height * 0.5f);

	CCSprite* sp_add_physical_2 = CCSprite::create(RES_add_physical);
	this->addChild(sp_add_physical_2);
	sp_add_physical_2->setPosition(ccp(vs.width * 0.29f, vs.height * 0.5f));

	__la_add_physical_2 = CCLabelAtlas::create("75", RES_number_style_1, 20, 20, '0');
	sp_add_physical_2->addChild(__la_add_physical_2);
	__la_add_physical_2->setAnchorPoint(ccp(0, 0.5f));
	__la_add_physical_2->setPosition(ccp(size_sp_add_physical_1.width, size_sp_add_physical_1.height * 0.5f));


	__item_rest3 = CCMenuItemSprite::create(
		CCSprite::create(RES_LayerRest_rest_3_0),
		CCSprite::create(RES_LayerRest_rest_3_1),
		this,
		menu_selector(LayerRest::menuCallbackRest)
		);
	__item_rest3->setPosition(vs.width * 0.54f, vs.height * 0.5f - size_item_rest1.height * 1.6f);

	CCSprite* sp_add_physical_3 = CCSprite::create(RES_add_physical);
	this->addChild(sp_add_physical_3);
	sp_add_physical_3->setPosition(ccp(vs.width * 0.29f, vs.height * 0.5f - size_item_rest1.height * 1.6f));

	__la_add_physical_3 = CCLabelAtlas::create("100", RES_number_style_1, 20, 20, '0');
	sp_add_physical_3->addChild(__la_add_physical_3);
	__la_add_physical_3->setAnchorPoint(ccp(0, 0.5f));
	__la_add_physical_3->setPosition(ccp(size_sp_add_physical_1.width, size_sp_add_physical_1.height * 0.5f));

	//菜单
	CCMenu *pMenu = CCMenu::create(item_close, __item_rest1, __item_rest2, __item_rest3, NULL);
	this->addChild(pMenu);
	pMenu->setPosition(CCPointZero);

	//进度条
	LayerProgress *layer_progress = LayerProgress::create();
	this->addChild(layer_progress, 10, 0);
	layer_progress->setVisible(false);
	layer_progress->setTouchEnabled(false);
	
	return true;
}
bool LayerRest::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	return true;
}
void LayerRest::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
}
void LayerRest::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
}
void LayerRest::ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent)
{
}

void LayerRest::menuCallbackClose(CCObject *pSender)
{
	this->removeFromParent();
}
void LayerRest::menuCallbackRest(CCObject *pSender)
{
	int glod = 0;
	if (pSender == __item_rest2)
	{//中级休息
		glod = 300;
	}
	else if (pSender == __item_rest3)
	{//高级休息
		glod = 500;
	}

	UserInfo *user_info = Topwo::getInstance()->getTopwoData()->getUserInfo();
	if (user_info->getCurrentGold() - glod >= 0)
	{
		LayerProgress *layer_progress = static_cast<LayerProgress*>(this->getChildByTag(0));
		layer_progress->setVisible(true);
		layer_progress->setTouchEnabled(true);
		layer_progress->setCallFunc(CCCallFuncO::create(this, callfuncO_selector(LayerRest::rest), pSender));
	}
}
void LayerRest::rest(CCObject *pSender)
{
	LayerProgress *layer_progress = static_cast<LayerProgress*>(this->getChildByTag(0));
	layer_progress->setVisible(false);
	layer_progress->setTouchEnabled(false);

	int physical = 0;
	int glod = 0;
	if (pSender == __item_rest1)
	{//普通休息
		physical = atoi(static_cast<CCLabelAtlas*>(__la_add_physical_1)->getString());
	}
	else if (pSender == __item_rest2)
	{//中级休息
		physical = atoi(static_cast<CCLabelAtlas*>(__la_add_physical_2)->getString());
		glod = 300;
	}
	else if (pSender == __item_rest3)
	{//高级休息
		physical = atoi(static_cast<CCLabelAtlas*>(__la_add_physical_3)->getString());
		glod = 500;
	}

	UserInfo *user_info = Topwo::getInstance()->getTopwoData()->getUserInfo();
	user_info->setCurrentPhysical(user_info->getCurrentPhysical() + physical);
	user_info->setCurrentGold(user_info->getCurrentGold() - glod);
	if (user_info->getCurrentPhysical() > 100)
	{//体力上限100
		user_info->setCurrentPhysical(100);
	}
}