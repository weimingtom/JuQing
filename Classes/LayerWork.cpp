#include "LayerWork.h"
#include "LayerExercise.h"
#include "LayerMission.h"
#include "LayerProgress.h"
#include "SceneMain.h"
#include "LayerRest.h"
#include "LayerHint.h"

LayerWork::LayerWork()
{

}
LayerWork::~LayerWork()
{
}
bool LayerWork::init()
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
void LayerWork::registerWithTouchDispatcher()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, kCCMenuHandlerPriority, true);
}
//初始化UI
bool LayerWork::initUI()
{
	CCPoint vo = CCDirector::sharedDirector()->getVisibleOrigin();
	CCSize vs = CCDirector::sharedDirector()->getVisibleSize();

	//背景
	CCScale9Sprite* sp_bg = CCScale9Sprite::create(RES_white_dialog);
	this->addChild(sp_bg);
	sp_bg->setContentSize(CCSizeMake(600.0f, 320.0f));
	CCSize size_sp_bg = sp_bg->getContentSize();
	sp_bg->setPosition(ccp(vs.width * 0.5f, vs.height * 0.5f));

	//标题
	CCSprite *sp_title = CCSprite::create(RES_LayerWork_title);
	this->addChild(sp_title);
	CCSize size_sp_title = sp_title->getContentSize();
	sp_title->setPosition(ccp(vs.width * 0.5f, (vs.height + size_sp_bg.height) * 0.5f - size_sp_title.height * 0.7f));

	//关闭项
	CCMenuItemSprite *item_close = CCMenuItemSprite::create(
		CCSprite::create(RES_btn_close_1_0),
		CCSprite::create(RES_btn_close_1_0),
		this,
		menu_selector(LayerWork::menuCallbackClose)
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

	//初级打工项
	CCMenuItemSprite *item_job_low = CCMenuItemSprite::create(
		CCSprite::create(RES_LayerWork_job_1_0),
		CCSprite::create(RES_LayerWork_job_1_1),
		this,
		menu_selector(LayerWork::menuCallbackWork)
		);
	CCSize size_item_job_low = item_job_low->getContentSize();
	item_job_low->setPosition(vs.width * 0.5f - size_item_job_low.width * 1.3f, vs.height * 0.45f);
	item_job_low->setTag(0);

	//中级打工项
	CCMenuItemSprite *item_job_mid = CCMenuItemSprite::create(
		CCSprite::create(RES_LayerWork_job_2_0),
		CCSprite::create(RES_LayerWork_job_2_1),
		this,
		menu_selector(LayerWork::menuCallbackWork)
		);
	item_job_mid->setPosition(vs.width * 0.5f, vs.height * 0.45f);
	item_job_mid->setTag(1);

	//高级打工项
	CCMenuItemSprite *item_job_high = CCMenuItemSprite::create(
		CCSprite::create(RES_LayerWork_job_3_0),
		CCSprite::create(RES_LayerWork_job_3_1),
		this,
		menu_selector(LayerWork::menuCallbackWork)
		);
	item_job_high->setPosition(vs.width * 0.5f + size_item_job_low.width * 1.3f, vs.height * 0.45f);
	item_job_high->setTag(2);

	//菜单
	CCMenu *menu = CCMenu::create(item_close, item_job_low, item_job_mid, item_job_high, NULL);
	this->addChild(menu);
	menu->setPosition(CCPointZero);

	//进度条
	LayerProgress *layer_progress = LayerProgress::create();
	this->addChild(layer_progress, 10, 0);
	layer_progress->setVisible(false);
	layer_progress->setTouchEnabled(false);

	return true;
}
bool LayerWork::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	return true;
}
void LayerWork::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
}
void LayerWork::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
}
void LayerWork::ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent)
{
}
void LayerWork::menuCallbackClose(CCObject* pSender)
{
	if (pSender)
	{
		Topwo::getInstance()->getTopwoAudio()->playEffect(1);
	}

	this->removeFromParent();
}
void LayerWork::menuCallbackWork(CCObject* pSender)
{
	if (pSender)
	{
		Topwo::getInstance()->getTopwoAudio()->playEffect(1);
	}

	TopwoTools *tl = Topwo::getInstance()->getTopwoTools();
	UserInfo *user_info = Topwo::getInstance()->getTopwoData()->getUserInfo();
	CCMenuItemSprite *item = static_cast<CCMenuItemSprite*>(pSender);
	int tag = item->getTag();
	int physical = 0;
	if (tag == 0)
	{
		physical = 15;
	}
	else if (tag == 1)
	{
		physical = 25;
	}
	else if (tag == 2)
	{
		physical = 50;
	}

	if (physical > user_info->getCurrentPhysical())
	{//体力不足
		this->addChild(LayerHint::createWith(CCLabelTTF::create(CCString::createWithFormat("%s%s", tl->getXmlString("Physical")->getCString(), tl->getXmlString("HintNotEnough")->getCString())->getCString(), "", 30), 2, this, callfuncN_selector(LayerWork::hintCallbackRest)), 10);
		return;
	}
	LayerProgress *layer_progress = static_cast<LayerProgress*>(this->getChildByTag(0));
	layer_progress->setVisible(true);
	layer_progress->setTouchEnabled(true);
	layer_progress->setCallFunc(CCCallFuncO::create(this, callfuncO_selector(LayerWork::work), pSender));
}
void LayerWork::work(CCObject* pSender)
{
	LayerProgress *layer_progress = static_cast<LayerProgress*>(this->getChildByTag(0));
	layer_progress->setVisible(false);
	layer_progress->setTouchEnabled(false);

	CCMenuItemSprite *item = static_cast<CCMenuItemSprite*>(pSender);
	int tag = item->getTag();
	int physical = 0;
	int gold = 0;
	if (tag == 0)
	{
		physical = 15;
		gold = 500;
	}
	else if (tag == 1)
	{
		physical = 25;
		gold = 1000;
	}
	else if (tag == 2)
	{
		physical = 50;
		gold = 2500;
	}
	UserInfo *user_info = Topwo::getInstance()->getTopwoData()->getUserInfo();
	user_info->setCurrentGold(user_info->getCurrentGold() + gold);
	user_info->setCurrentPhysical(user_info->getCurrentPhysical() - physical);

	SceneMain* scene_main = static_cast<SceneMain*>(CCDirector::sharedDirector()->getRunningScene()->getChildByTag(0));
	scene_main->updateMe();
}
void LayerWork::hintCallbackRest(CCNode *node)
{
	if (node->getTag() == 1)
	{
		this->getParent()->addChild(LayerRest::create(), 10);
		this->removeFromParent();
	}
}