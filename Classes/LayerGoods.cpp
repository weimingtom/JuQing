#include "LayerGoods.h"
#include "LayerExercise.h"
#include "LayerMission.h"
#include "SceneMain.h"

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

	UserInfo *user_info = Topwo::getInstance()->getTopwoData()->getUserInfo();

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
	CCSprite* sp_goods_1 = CCSprite::create(RES_LayerGoods_tipo);
	this->addChild(sp_goods_1, 0 ,1);
	CCSize size_sp_goods_1 = sp_goods_1->getContentSize();
	sp_goods_1->setPosition(ccp(vs.width * 0.5f - size_sp_goods_1.width * 2.04f, vs.height * 0.43f));

	CCLabelAtlas* la_value = CCLabelAtlas::create(CCString::createWithFormat("%d", getGoodsBonus(user_info->getCurrentGoodsLevelTiPo()))->getCString(), RES_number_style_2, 9, 15, '+');
	sp_goods_1->addChild(la_value, 0, 0);
	la_value->setAnchorPoint(ccp(0, 0.5f));
	la_value->setPosition(ccp(size_sp_goods_1.width * 0.65f, size_sp_goods_1.height * 0.48f));

	la_value = CCLabelAtlas::create(CCString::createWithFormat("%d", getGoodsPrice(user_info->getCurrentGoodsLevelTiPo()))->getCString(), RES_number_style_2, 9, 15, '+');
	sp_goods_1->addChild(la_value, 0, 1);
	la_value->setAnchorPoint(ccp(0, 0.5f));
	la_value->setPosition(ccp(size_sp_goods_1.width * 0.56f, size_sp_goods_1.height * 0.35f));

	CCMenuItemSprite* item_buy_goods_1 = CCMenuItemSprite::create(
		CCSprite::create(RES_btn_buy_0),
		CCSprite::create(RES_btn_buy_1),
		this,
		menu_selector(LayerGoods::menuCallbackBuy)
		);
	item_buy_goods_1->setPosition(ccp(vs.width * 0.5f - size_sp_goods_1.width * 2.04f, vs.height * 0.31f));
	item_buy_goods_1->setTag(1);

	//购买物品2
	CCSprite* sp_goods_2 = CCSprite::create(RES_LayerGoods_meili);
	this->addChild(sp_goods_2, 0, 2);
	sp_goods_2->setPosition(ccp(vs.width * 0.5f - size_sp_goods_1.width * 1.02f, vs.height * 0.43f));

	la_value = CCLabelAtlas::create(CCString::createWithFormat("%d", getGoodsBonus(user_info->getCurrentGoodsLevelMeiLi()))->getCString(), RES_number_style_2, 9, 15, '+');
	sp_goods_2->addChild(la_value, 0, 0);
	la_value->setAnchorPoint(ccp(0, 0.5f));
	la_value->setPosition(ccp(size_sp_goods_1.width * 0.65f, size_sp_goods_1.height * 0.48f));

	la_value = CCLabelAtlas::create(CCString::createWithFormat("%d", getGoodsPrice(user_info->getCurrentGoodsLevelMeiLi()))->getCString(), RES_number_style_2, 9, 15, '+');
	sp_goods_2->addChild(la_value, 0, 1);
	la_value->setAnchorPoint(ccp(0, 0.5f));
	la_value->setPosition(ccp(size_sp_goods_1.width * 0.56f, size_sp_goods_1.height * 0.35f));

	CCMenuItemSprite* item_buy_goods_2 = CCMenuItemSprite::create(
		CCSprite::create(RES_btn_buy_0),
		CCSprite::create(RES_btn_buy_1),
		this,
		menu_selector(LayerGoods::menuCallbackBuy)
		);
	item_buy_goods_2->setPosition(ccp(vs.width * 0.5f - size_sp_goods_1.width * 1.02f, vs.height * 0.31f));
	item_buy_goods_2->setTag(2);

	//购买物品3
	CCSprite* sp_goods_3 = CCSprite::create(RES_LayerGoods_zhili);
	this->addChild(sp_goods_3, 0, 3);
	sp_goods_3->setPosition(ccp(vs.width * 0.5f, vs.height * 0.43f));

	la_value = CCLabelAtlas::create(CCString::createWithFormat("%d", getGoodsBonus(user_info->getCurrentGoodsLevelZhiLi()))->getCString(), RES_number_style_2, 9, 15, '+');
	sp_goods_3->addChild(la_value, 0, 0);
	la_value->setAnchorPoint(ccp(0, 0.5f));
	la_value->setPosition(ccp(size_sp_goods_1.width * 0.65f, size_sp_goods_1.height * 0.48f));

	la_value = CCLabelAtlas::create(CCString::createWithFormat("%d", getGoodsPrice(user_info->getCurrentGoodsLevelZhiLi()))->getCString(), RES_number_style_2, 9, 15, '+');
	sp_goods_3->addChild(la_value, 0, 1);
	la_value->setAnchorPoint(ccp(0, 0.5f));
	la_value->setPosition(ccp(size_sp_goods_1.width * 0.56f, size_sp_goods_1.height * 0.35f));

	CCMenuItemSprite* item_buy_goods_3 = CCMenuItemSprite::create(
		CCSprite::create(RES_btn_buy_0),
		CCSprite::create(RES_btn_buy_1),
		this,
		menu_selector(LayerGoods::menuCallbackBuy)
		);
	item_buy_goods_3->setPosition(ccp(vs.width * 0.5f, vs.height * 0.31f));
	item_buy_goods_3->setTag(3);

	//购买物品4
	CCSprite* sp_goods_4 = CCSprite::create(RES_LayerGoods_eq);
	this->addChild(sp_goods_4, 0, 4);
	sp_goods_4->setPosition(ccp(vs.width * 0.5f + size_sp_goods_1.width * 1.02f, vs.height * 0.43f));

	la_value = CCLabelAtlas::create(CCString::createWithFormat("%d", getGoodsBonus(user_info->getCurrentGoodsLevelEQ()))->getCString(), RES_number_style_2, 9, 15, '+');
	sp_goods_4->addChild(la_value, 0, 0);
	la_value->setAnchorPoint(ccp(0, 0.5f));
	la_value->setPosition(ccp(size_sp_goods_1.width * 0.65f, size_sp_goods_1.height * 0.48f));

	la_value = CCLabelAtlas::create(CCString::createWithFormat("%d", getGoodsPrice(user_info->getCurrentGoodsLevelEQ()))->getCString(), RES_number_style_2, 9, 15, '+');
	sp_goods_4->addChild(la_value, 0, 1);
	la_value->setAnchorPoint(ccp(0, 0.5f));
	la_value->setPosition(ccp(size_sp_goods_1.width * 0.56f, size_sp_goods_1.height * 0.35f));

	CCMenuItemSprite* item_buy_goods_4 = CCMenuItemSprite::create(
		CCSprite::create(RES_btn_buy_0),
		CCSprite::create(RES_btn_buy_1),
		this,
		menu_selector(LayerGoods::menuCallbackBuy)
		);
	item_buy_goods_4->setPosition(ccp(vs.width * 0.5f + size_sp_goods_1.width * 1.02f, vs.height * 0.31f));
	item_buy_goods_4->setTag(4);

	//购买物品5
	CCSprite *sp_goods_5 = CCSprite::create(RES_LayerGoods_ganxing);
	this->addChild(sp_goods_5, 0, 5);
	sp_goods_5->setPosition(ccp(vs.width * 0.5f + size_sp_goods_1.width * 2.04f, vs.height * 0.43f));

	la_value = CCLabelAtlas::create(CCString::createWithFormat("%d", getGoodsBonus(user_info->getCurrentGoodsLevelGanXing()))->getCString(), RES_number_style_2, 9, 15, '+');
	sp_goods_5->addChild(la_value, 0, 0);
	la_value->setAnchorPoint(ccp(0, 0.5f));
	la_value->setPosition(ccp(size_sp_goods_1.width * 0.65f, size_sp_goods_1.height * 0.48f));

	la_value = CCLabelAtlas::create(CCString::createWithFormat("%d", getGoodsPrice(user_info->getCurrentGoodsLevelGanXing()))->getCString(), RES_number_style_2, 9, 15, '+');
	sp_goods_5->addChild(la_value, 0, 1);
	la_value->setAnchorPoint(ccp(0, 0.5f));
	la_value->setPosition(ccp(size_sp_goods_1.width * 0.56f, size_sp_goods_1.height * 0.35f));

	CCMenuItemSprite *item_buy_goods_5 = CCMenuItemSprite::create(
		CCSprite::create(RES_btn_buy_0),
		CCSprite::create(RES_btn_buy_1),
		this,
		menu_selector(LayerGoods::menuCallbackBuy)
		);
	item_buy_goods_5->setPosition(ccp(vs.width * 0.5f + size_sp_goods_1.width * 2.04f, vs.height * 0.31f));
	item_buy_goods_5->setTag(5);

	CCMenu *menu = CCMenu::create(item_close, item_buy_goods_1, item_buy_goods_2, item_buy_goods_3, item_buy_goods_4, item_buy_goods_5, NULL);
	this->addChild(menu, 0, 0);
	menu->setPosition(CCPointZero);

	updateMe();

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
void LayerGoods::menuCallbackBuy(CCObject* pSender)
{
	if (!pSender)
	{
		return;
	}
	UserInfo *user_info = Topwo::getInstance()->getTopwoData()->getUserInfo();

	CCMenuItemSprite* item = static_cast<CCMenuItemSprite*>(pSender);
	int tag = item->getTag();
	CCSprite* sprite = static_cast<CCSprite*>(this->getChildByTag(tag));
	CCLabelAtlas* la = static_cast<CCLabelAtlas*>(sprite->getChildByTag(1));
	int need_gold = atoi(la->getString());
	int cur_gold = user_info->getCurrentGold();
	if (need_gold > cur_gold)
	{
		return;
	}
	user_info->setCurrentGold(cur_gold - need_gold);
	if (tag == 1)
	{
		user_info->setCurrentGoodsLevelTiPo(user_info->getCurrentGoodsLevelTiPo() + 1);
	}
	else if (tag == 2)
	{
		user_info->setCurrentGoodsLevelMeiLi(user_info->getCurrentGoodsLevelMeiLi() + 1);
	}
	else if (tag == 3)
	{
		user_info->setCurrentGoodsLevelZhiLi(user_info->getCurrentGoodsLevelZhiLi() + 1);
	}
	else if (tag == 4)
	{
		user_info->setCurrentGoodsLevelEQ(user_info->getCurrentGoodsLevelEQ() + 1);
	}
	else if (tag == 5)
	{
		user_info->setCurrentGoodsLevelGanXing(user_info->getCurrentGoodsLevelGanXing() + 1);
	}

	updateMe();
}
void LayerGoods::updateMe()
{
	UserInfo *user_info = Topwo::getInstance()->getTopwoData()->getUserInfo();

	CCMenu* menu = static_cast<CCMenu*>(this->getChildByTag(0));
	//体魄
	int goods_level = 0;
	CCMenuItemSprite* item = NULL;
	CCSprite* sprite = NULL;
	CCLabelAtlas* la = NULL;
	for (int i = 1; i <= 5; i++)
	{
		if (i == 1)
		{
			goods_level = user_info->getCurrentGoodsLevelTiPo();
		}
		else if (i == 2)
		{
			goods_level = user_info->getCurrentGoodsLevelMeiLi();
		}
		else if (i == 3)
		{
			goods_level = user_info->getCurrentGoodsLevelZhiLi();
		}
		else if (i == 4)
		{
			goods_level = user_info->getCurrentGoodsLevelEQ();
		}
		else if (i == 5)
		{
			goods_level = user_info->getCurrentGoodsLevelGanXing();
		}
		item = static_cast<CCMenuItemSprite*>(menu->getChildByTag(i));
		if (goods_level >= 9)
		{
			item->setEnabled(false);
			item->setColor(ccc3(128, 128, 128));
		}
		sprite = static_cast<CCSprite*>(this->getChildByTag(i));
		la = static_cast<CCLabelAtlas*>(sprite->getChildByTag(0));
		la->setString(CCString::createWithFormat("%d", getGoodsBonus(goods_level))->getCString());
		la = static_cast<CCLabelAtlas*>(sprite->getChildByTag(1));
		la->setString(CCString::createWithFormat("%d", getGoodsPrice(goods_level))->getCString());
	}

	SceneMain* scene_main = static_cast<SceneMain*>(CCDirector::sharedDirector()->getRunningScene()->getChildByTag(0));
	scene_main->updateMe();
}
int LayerGoods::getGoodsPrice(int level)
{
	int iRet = 0;
	switch (level)
	{
	case 0:
		iRet = 500;
		break;
	case 1:
		iRet = 1000;
		break;
	case 2:
		iRet = 1500;
		break;
	case 3:
		iRet = 2500;
		break;
	case 4:
		iRet = 3500;
		break;
	case 5:
		iRet = 4500;
		break;
	case 6:
		iRet = 6000;
		break;
	case 7:
		iRet = 7500;
		break;
	case 8:
		iRet = 9000;
	case 9:
		iRet = 9000;
		break;
	}
	return iRet;
}
int LayerGoods::getGoodsBonus(int level)
{
	int iRet = 0;
	switch (level)
	{
	case 0:
		iRet = 1;
		break;
	case 1:
		iRet = 2;
		break;
	case 2:
		iRet = 3;
		break;
	case 3:
		iRet = 5;
		break;
	case 4:
		iRet = 7;
		break;
	case 5:
		iRet = 9;
		break;
	case 6:
		iRet = 12;
		break;
	case 7:
		iRet = 15;
		break;
	case 8:
		iRet = 18;
	case 9:
		iRet = 18;
		break;
	}
	return iRet;
}